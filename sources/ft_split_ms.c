/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:41:57 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/10 16:46:47 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_words(const char *str, char delimiter)
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
			in_quotes = !in_quotes;
		if (!in_quotes && str[i] == delimiter)
		{
			if (i > 0 && str[i - 1] != delimiter)
				count++;
		}
		i++;
	}
	if (i > 0 && str[i - 1] != delimiter)
		count++;
	return (count);
}

static char	**last_word(char **result, const char *str, int start, int *index)
{
	int	length;
	int	i;

	length = 0;
	i = *index;
	length = ft_strlen(str) - start;
	result[i] = (char *)malloc((length + 1) * sizeof(char));
	if (result[i] == NULL)
		return (free_split(result, i), NULL);
	ft_strcpy(result[i], str + start);
	result[i][length] = '\0';
	i++;
	*index = i;
	return (result);
}

static int	ft_strcpy_ms_split(char **result, const char *str, int *iter,
		t_split_ms_vars *var)
{
	int	length;
	int	idx;
	int	st;
	int	i;

	st = var->st;
	idx = var->idx;
	i = *iter;
	length = i - st;
	result[idx] = (char *)malloc((length + 1) * sizeof(char));
	if (result[idx] == NULL)
	{
		free_split(result, idx);
		return (free(result), 1);
	}
	ft_strncpy(result[idx], str + st, length);
	result[idx][length] = '\0';
	idx++;
	st = -1;
	var->idx = idx;
	var->st = st;
	return (0);
}

static char	**ft_alloc_splited_str(char **result, const char *str,
		char delimiter, t_split_ms_vars *var)
{
	int	i;
	int	in_quotes;

	in_quotes = 0;
	var->idx = var->index;
	var->st = var->start;
	i = -1;
	while (str[++i])
	{
		ft_in_quotes(str[i], &in_quotes);
		if (!in_quotes && str[i] == delimiter)
		{
			if (var->st != -1)
				if (ft_strcpy_ms_split(result, str, &i, var) == 1)
					return (NULL);
		}
		else if (var->st == -1)
			var->st = i;
	}
	var->index = var->idx;
	var->start = var->st;
	return (result);
}

char	**ft_split_ms(const char *str, char delimiter)
{
	int				word_count;
	t_split_ms_vars	vars;
	char			**result;

	word_count = count_words(str, delimiter);
	vars.start = -1;
	vars.index = 0;
	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (str == NULL)
		return (NULL);
	if (result == NULL)
		return (NULL);
	result = ft_alloc_splited_str(result, str, delimiter, &vars);
	if (vars.start != -1)
		result = last_word(result, str, vars.start, &vars.index);
	result[vars.index] = NULL;
	return (result);
}
