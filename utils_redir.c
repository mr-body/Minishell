/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 02:13:12 by waalexan          #+#    #+#             */
/*   Updated: 2024/11/07 16:49:08 by gkomba           ###   ########.fr       */
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
	int		i;
	int		qt_flag;

	i = *index;
	qt_flag = *is_quote;
	if (str[i] == '"' || str[i] == '\'')
	{
		if (!qt_flag)
		{
			qt_flag = 1;
			*quote_type = (int)str[i];
		}
		else if (str[i] == *quote_type)
			qt_flag = 0;
		i++;
		*index = i;
		*is_quote = qt_flag;
	}
}

// int	is_redir(char *str)
// {
// 	int	i;
// 	int	is_quote;
// 	int	redirect;
// 	int	quote_type;

// 	i = 0;
// 	is_quote = 0;
// 	redirect = 0;
// 	while (str[i])
// 	{
// 		verify_redir_is_in_qt(str, &i, &is_quote, &quote_type);
// 		if (!is_quote)
// 		{
// 			redirect = return_redir_type(str[i], str[i + 1]);
// 			if (redirect)
// 				return (redirect);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int	is_redir(char *str)
{
	int	i;
	int	is_quote;
	int	redirect;
	int	quote_type;

	i = 0;
	is_quote = 0;
	redirect = 0;
	while (str[i] != '\0' && str[i] != '0')
	{
		verify_redir_is_in_qt(str, &i, &is_quote, &quote_type);
		if (!is_quote)
		{
			if (str[i] == '0')
				return (0);
			if (str[i + 1] != '\0')
				redirect = return_redir_type(str[i], str[i + 1]);
			else
				redirect = return_redir_type(str[i], '\0');

			if (redirect != 0)
				return (redirect);
		}
		i++;
	}
	return (0);
}

