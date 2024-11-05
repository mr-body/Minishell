/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:35:50 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/05 18:40:23 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verify_pipes_syntax(t_minishell *minishell)
{
	int	i;

	i = 0;
	minishell->verify_syntax = ft_split_ms(minishell->command, ' ');
	while (minishell->verify_syntax[i])
	{
		if (ft_strncmp(minishell->verify_syntax[i], "|", 1) == 0)
		{
			if (minishell->verify_syntax[i + 1] == NULL)
			{
				ft_putendl_fd("syntax error near unexpected token `newline'",
					2);
				return (ft_free_matriz(minishell->verify_syntax), 2);
			}
			if (ft_strncmp(minishell->verify_syntax[i + 1], "|", 1) == 0)
			{
				ft_putendl_fd("syntax error near unexpected token `|'", 2);
				return (ft_free_matriz(minishell->verify_syntax), 2);
			}
		}
		i++;
	}
	return (ft_free_matriz(minishell->verify_syntax), 0);
}

int	verify_redir_syntax(t_minishell *minishell, char *redir_type)
{
	int	i;

	i = 0;
	minishell->verify_syntax = ft_split_ms(minishell->redirect_command, ' ');
	while (minishell->verify_syntax[i])
	{
		if (ft_strncmp(minishell->verify_syntax[i], redir_type, 1) == 0)
		{
			if (minishell->verify_syntax[i + 1] == NULL)
			{
				ft_putendl_fd("syntax error near unexpected token `newline'",
					2);
				return (ft_free_matriz(minishell->verify_syntax), 2);
			}
			if ((ft_strncmp(minishell->verify_syntax[i + 1], redir_type,
						1) == 0) || ft_strncmp(minishell->verify_syntax[i + 1],
					"|", 1) == 0)
			{
				ft_putendl_fd("syntax error near unexpected token `newline'",
					2);
				return (ft_free_matriz(minishell->verify_syntax), 2);
			}
		}
		i++;
	}
	return (ft_free_matriz(minishell->verify_syntax), 0);
}

int	syntax_checker(t_minishell *minishell)
{
	minishell->exit_status = verify_pipes_syntax(minishell);
	if (minishell->exit_status == 2)
		return (2);
	minishell->status = verify_redir_syntax(minishell, ">");
	if (minishell->status == 2)
		return (2);
	minishell->status = verify_redir_syntax(minishell, "<");
	if (minishell->status == 2)
		return (2);
	return (0);
}