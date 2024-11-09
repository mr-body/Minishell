/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:39:46 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/09 14:29:49 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_quotes(char *str, char quote_type)
{
	int	i;
	int	quote_count;

	i = 0;
	quote_count = 0;
	while (str[i])
	{
		if (str[i] == quote_type)
			quote_count++;
		i++;
	}
	return (quote_count);
}

char	*handle_quotes(char *tmp)
{
	if (check_quotes(tmp, '\"') > 1 && check_quotes(tmp, '\"') % 2 == 0)
	{
		tmp = ft_strtrim(tmp, "\"");
		return (tmp);
	}
	if (check_quotes(tmp, '\'') > 1 && check_quotes(tmp, '\'') % 2 == 0)
	{
		tmp = ft_strtrim(tmp, "\'");
		return (tmp);
	}
	return (NULL);
}

int	unbalanced_quotes(char *str)
{
	int	double_quotes_count;
	int	single_quotes_count;

	double_quotes_count = ft_count_chr_occurrency_str(str, '\"');
	single_quotes_count = ft_count_chr_occurrency_str(str, '\'');
	if ((double_quotes_count % 2 != 0) && (single_quotes_count % 2 != 0))
	{
		ft_putendl_fd("Error: unbalanced quotes", 2);
		return (1);
	}
	return (0);
}

void	ft_in_quotes(char c, int *in_quotes)
{
	if (c == '"' || c == '\'')
		*in_quotes = !*in_quotes;
}

void	ft_delete_quotes(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\"' || str[i] != '\'')
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
}
