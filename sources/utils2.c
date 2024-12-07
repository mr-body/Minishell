/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:41:08 by gkomba            #+#    #+#             */
/*   Updated: 2024/12/07 19:28:23 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redir_is_followed_by_pipe(const char *str)
{
	if (ft_strncmp(str, "<|", 2) == 0 || ft_strncmp(str, "<<|",
			3) == 0 || ft_strncmp(str, ">|", 2) == 0
		|| ft_strncmp(str, ">>|", 3) == 0)
	{
		redir_syntax_error("PANCAKE");
		return (1);
	}
	return (0);
}

int	redir_is_not_followed_by_pipe(char **matriz)
{
	int	i;
	int	qt_flag;

	i = 0;
	qt_flag = 0;
	while (matriz[i])
	{
		if (matriz[i][0] != '\0' && ((matriz[i][0] == '\''
					&& matriz[i][ft_strlen(matriz[i]) - 1] == '\'')
				|| (matriz[i][0] == '\"' && matriz[i][ft_strlen(matriz[i])
					- 1] == '\"')))
		{
			i++;
			qt_flag = 1;
			continue ;
		}
		if (!qt_flag && matriz[i][0] != '\0')
		{
			if (redir_is_followed_by_pipe(matriz[i]))
				return (1);
		}
		i++;
		qt_flag = 0;
	}
	return (0);
}

int	in_quotes(t_split_redir_cmd *vars, char *command)
{
	if (command[vars->i] == '"' || command[vars->i] == '\'')
	{
		vars->in_quotes = !vars->in_quotes;
		vars->i++;
		return (1);
	}
	return (0);
}

int	whitespace_and_syntax(t_minishell *minishell, char **data)
{
	if (minishell->readline[0] == '|')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		return (ft_free_matriz(data), 1);
	}
	if (minishell->readline[0] == '\n' || minishell->readline[0] == '\0'
		|| (minishell->readline[0] == '\t' && minishell->readline[1] == '\0'))
		return (ft_free_matriz(data), 1);
	if (syntax_checker(minishell) == 2)
		return (ft_free_matriz(data), 2);
	return (0);
}
