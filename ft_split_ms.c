/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:41:57 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/04 18:53:16 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words(const char *str, char delimiter)
{
	int	in_quotes;
	int	count;
	int	i;

	in_quotes = 0;
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			in_quotes = !in_quotes;
		}
		if (!in_quotes && str[i] == delimiter)
		{
			if (i > 0 && str[i - 1] != delimiter)
			{
				count++;
			}
		}
		i++;
	}
	if (i > 0 && str[i - 1] != delimiter)
	{
		count++;
	}
	return (count);
}

char	**ft_split_ms(const char *str, char delimiter)
{
	int		word_count;
	int		in_quotes;
	int		start;
	int		index;
	int		i;
	int		j;
	int		length;
	char	type_qt;
	char	**result;

	word_count = count_words(str, delimiter);
	in_quotes = 0;
	start = -1;
	index = 0;
	result = malloc((word_count + 1) * sizeof(char *));
	i = -1;
	if (str == NULL)
		return (NULL);
	if (result == NULL)
		return (NULL);
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			in_quotes = !in_quotes;
			type_qt = str[i];
		}
		if (!in_quotes && str[i] == delimiter)
		{
			if (start != -1)
			{
				length = i - start;
				result[index] = malloc((length + 1) * sizeof(char));
				if (result[index] == NULL)
				{
					j = -1;
					while (++j < index)
						free(result[j]);
					free(result);
					return (NULL);
				}
				strncpy(result[index], str + start, length);
				result[index][length] = '\0';
				index++;
				start = -1;
			}
		}
		else
		{
			if (start == -1)
				start = i;
		}
	}
	if (start != -1)
	{
		length = strlen(str) - start;
		result[index] = malloc((length + 1) * sizeof(char));
		if (result[index] == NULL)
		{
			j = -1;
			while (++j < index)
				free(result[j]);
			free(result);
			return (NULL);
		}
		strcpy(result[index], str + start);
		result[index][length] = '\0';
		index++;
	}
	result[index] = NULL;
	return (result);
}
