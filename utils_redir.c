/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 02:13:12 by waalexan          #+#    #+#             */
/*   Updated: 2024/11/08 08:50:02 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	return_redir_type(char curr_c, char next_c)
{
	if (curr_c == '>' && next_c == '>')
		return (R_APPEND_O);
	else if (curr_c == '<' && next_c == '<')
		return (R_APPEND_I);
	else if (curr_c == '>')
		return (R_TRUNC_O);
	else if (curr_c == '<')
		return (R_TRUNC_I);
	return (0);
}

void	verify_redir_is_in_qt(char *str, int *index, int *is_quote,
			int *quote_type)
{
	int		qt_flag;

	qt_flag = *is_quote;
	if (str[*index] == '"' || str[*index] == '\'')
	{
		if (!qt_flag)
		{
			qt_flag = 1;
			*quote_type = (int)str[*index];
		}
		else if (str[*index] == *quote_type)
			qt_flag = 0;
		*index++;
		*is_quote = qt_flag;
	}
}

int	is_redir(char *str)
{
	int	i;
	int	is_quote;
	int	redirect;
	int	quote_type;

	i = -1;
	is_quote = 0;
	redirect = 0;
	while (str[++i])
	{
		verify_redir_is_in_qt(str, &i, &is_quote, &quote_type);
		if (!is_quote)
		{
			redirect = return_redir_type(str[i], str[i + 1]);
			if (redirect)
				return (redirect);
		}
	}
	return (0);
}
