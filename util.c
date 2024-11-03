/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:24:38 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/03 11:40:17 by gkomba           ###   ########.fr       */
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

char	**ft_adjust_data(char **data, int *quotes)
{
	int		i;
	int		j;
	char	**new;
	char	*tmp;
	char	*new_tmp;
	char	*old_tmp;
	char delimiter;

	i = -1;
	j = 0;
	new = (char **)malloc(sizeof(char *) * (ft_matriz_len(data) + 1));
	tmp = NULL;
	if (!new)
		return (NULL);
	ft_memset(new, 0, sizeof(new));
	while (data[++i])
	{
		delimiter = 0;

		if(data[i][0] == '\"' || data[i][0] == '\'')
			delimiter = data[i][0];
		else
		{
			if(ft_strchr(data[i], '\"'))
				delimiter = '\"';
			else if(ft_strchr(data[i], '\''))
				delimiter = '\'';
		}

		if (ft_count_chr_occurrency_str(data[i], delimiter) % 2 == 0)
		{
			old_tmp = ft_strdup("");
			new[j] = expand_env_var(data[i], old_tmp, delimiter);
		}
		else
		{
			old_tmp = tmp;
			tmp = strdup(data[i]);
			free(old_tmp);
			if (!tmp)
			{
				printf("Error: malloc failed\n");
				free(tmp);
				return (NULL);
			}
			if (data[i + 1])
			{
				i++;
				while (data[i] && ft_count_chr_occurrency_str(tmp, delimiter)
					% 2 != 0)
				{
					new_tmp = ft_strcat(tmp, data[i], ' ');
					free(tmp);
					tmp = new_tmp;
					if (data[i + 1] && ft_count_chr_occurrency_str(tmp, delimiter)
						% 2 != 0)
						i++;
					else
					{
						printf("Error: unbalanced quotes1\n");
						break ;
					}
				}
			}
			if (ft_count_chr_occurrency_str(tmp, delimiter) % 2 == 0)
			{
				old_tmp = ft_strdup("");
				new[j] = expand_env_var(tmp, old_tmp, delimiter);
			}
			else
			{
				free(tmp);
				printf("Error: unbalanced quotes2\n");
				*quotes = 0;
			}
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
	int		quotes;

	// ft_memset(net_args, 0, sizeof(net_args));
	// ft_memset(&raw_data, 0, sizeof(raw_data));
	if(unbalanced_quotes(prompt))
		return NULL;
	quotes = 1;
	raw_data = ft_split(prompt, ' ');
	net_data = ft_adjust_data(raw_data, &quotes);
	if(!quotes)
	{
		ft_free_matriz(net_data);
		ft_free_matriz(raw_data);
		ft_putendl_fd("Error: unbalanced quotes", 2);
		return NULL;
	}
	ft_free_matriz(raw_data);
	return (net_data);

}