/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:24:38 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/01 15:15:26 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_strtok(char *str, char *delimiter,
		char result[MAX_WORDS][MAX_WORD_LENGTH])
{
	int	i;
	int	j;
	int	k;
	int	in_word;

	i = 0;
	j = 0;
	k = 0;
	in_word = 0;
	while (str[i])
	{
		if (ft_strchr(delimiter, str[i]))
		{
			if (in_word)
			{
				result[j][k] = '\0';
				j++;
				k = 0;
				in_word = 0;
			}
		}
		else
		{
			if (k < MAX_WORD_LENGTH - 1)
			{
				result[j][k] = str[i];
				k++;
			}
			in_word = 1;
		}
		i++;
	}
	if (in_word)
	{
		result[j][k] = '\0';
		j++;
	}
	i = j;
	while (i < MAX_WORDS)
	{
		result[i][0] = '\0';
		i++;
	}
}

char	**ft_adjust_data(char **data)
{
	int		i;
	int		j;
	char	**new;
	char	*tmp;
	char	*new_tmp;

	i = -1;
	j = 0;
	new = malloc(sizeof(char *) * (ft_matriz_len(data) + 1));
	tmp = NULL;
	if (!new)
		return (NULL);
	while (data[++i])
	{
		if (ft_count_chr_occurrency_str(data[i], '\"') % 2 == 0)
			new[j] = data[i];
		else
		{
			tmp = strdup(data[i]);
			if (!tmp)
				return (NULL);
			if (data[i + 1])
			{
				i++;
				while (data[i] && ft_count_chr_occurrency_str(tmp, '\"')
					% 2 != 0)
				{
					new_tmp = ft_strcat(tmp, data[i], ' ');
					free(tmp);
					tmp = new_tmp;
					if (data[i + 1] && ft_count_chr_occurrency_str(tmp, '\"')
						% 2 != 0)
						i++;
					else
						break ;
				}
			}
			if (ft_count_chr_occurrency_str(tmp, '\"') % 2 == 0)
				new[j] = tmp;
		}
		j++;
	}
	new[j] = NULL;
	return (new);
}

char	**net_args(char *prompt)
{
	char	**raw_data;
	char	**net_data;
	char	**data;
	int		qt;

	qt = unbalanced_quotes(prompt);
	if (qt == 1)
		return (NULL);
	else
	{
		raw_data = ft_split(prompt, ' ');
		net_data = ft_adjust_data(raw_data);
		data = ft_extended(net_data);
		return (data);
	}
	return (NULL);
}
