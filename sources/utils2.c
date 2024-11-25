/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:41:08 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/15 12:56:06 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redir_is_not_followed_by_pipe(char **matriz)
{
	int	i;

	i = 0;
	while (matriz[i])
	{
		if (ft_strncmp(matriz[i], "<|", 2) == 0)
		{
			redir_syntax_error("PANCAKE");
			return (1);
		}
		else if (ft_strncmp(matriz[i], "<<|", 3) == 0)
		{
			redir_syntax_error("PANCAKE");
			return (1);
		}
		i++;
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

void	ft_prompt_sms(char c)
{
	if (c == 'g')
		ft_putendl_fd(AZUL "gkomba >> Welcome Human 🪐" RESET, 1);
	else if (c == 'w')
		ft_putendl_fd(VERDE "waalexa >> Now. Waalexan is on control 🌍" RESET,
			1);
	else if (c == 'm')
		ft_putendl_fd(AMARELO "minishell >> Welcome to minishell 🌌" RESET, 1);
}

int	whitespace_and_syntax(t_minishell *minishell, char **data)
{
	if (minishell->readline[0] == '\n' || minishell->readline[0] == '\0'
		|| minishell->readline[0] == '\t')
		return (ft_free_matriz(data), 1);
	if (syntax_checker(minishell) == 2)
		return (ft_free_matriz(data), 2);
	return (0);
}

void	close_minishell_fd(int fd1, int fd2)
{
	dup2(fd1, fd2);
	close(fd1);
}
