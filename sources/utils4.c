/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:41:08 by gkomba            #+#    #+#             */
/*   Updated: 2024/12/06 12:45:19 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	verif_redir(t_minishell *minishell)
{
	int	redir;
	int	retrn;

	redir = 0;
	if (minishell->args)
		free_data(minishell->args);
	if (extract_command(minishell, &redir, &retrn) != 0)
		exit(1);
	if (redir == R_TRUNC_O)
		redir_trunc_o(minishell, 0);
	else if (redir == R_APPEND_O)
		redir_append_o(minishell, 0);
	else if (redir == R_TRUNC_I)
		redir_trunc_in(minishell, 0);
	else if (redir == R_APPEND_I)
		redir_append_in(minishell, 0);
	if (!minishell->args || minishell->not_flag == -1)
	{
		free_data(minishell->args);
		minishell->not_flag = 0;
		exit(1);
	}
}

void	close_minishell_fd(int fd1, int fd2)
{
	dup2(fd1, fd2);
	close(fd1);
}

void	control_center(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

int	invalid_path(char *path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (path[i] == '/' && path[i + 1] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_last_pipe(char *str)
{
	int	i;
	int	fg;

	i = ft_strlen(str);
	fg = 0;
	while (0 <= i--)
	{
		if (str[i] == '|')
			fg++;
		else if (str[i] == 32 || str[i] == 9)
			continue ;
		else
			break ;
	}
	return (fg);
}
