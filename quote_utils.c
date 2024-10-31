/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:39:46 by gkomba            #+#    #+#             */
/*   Updated: 2024/10/31 10:47:10 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_quotes(char *tmp)
{
	char	*old_tmp;

	old_tmp = handle_quotes(tmp);
	if (!old_tmp)
	{
		free(tmp);
		return (NULL);
	}
	else
	{
		free(tmp);
		return (old_tmp);
	}
	return (tmp);
}

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

char *handle_quotes(char *tmp)
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

int   unbalanced_quotes(char *str)
{
    if (ft_count_chr_occurrency_str(str, '\"') % 2 != 0)
		return (ft_putendl_fd("Error: unbalanced quotes\n", 2), 1);
	else if (ft_count_chr_occurrency_str(str, '\'') % 2 != 0)
        return (ft_putendl_fd("Error: unbalanced quotes\n", 2), 1);
    return (0);
}
