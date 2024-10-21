/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:35:50 by gkomba            #+#    #+#             */
/*   Updated: 2024/10/21 12:41:16 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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