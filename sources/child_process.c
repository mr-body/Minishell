/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:57:35 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/22 09:29:37 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_child_process(t_minishell *minishell)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror("fork error: ");
	else if (pid == 0)
	{
		verif_redir(minishell);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (minishell->fd_type == 0)
			dup2(minishell->fd, STDOUT_FILENO);
		else
			dup2(minishell->fd, STDIN_FILENO);
		if (shell(minishell->args->args, 0, minishell) == -1)
		{
			ft_print_command_error(minishell->args->args[0]);
			exit(127);
		}
		close(minishell->fd);
	}
	else
		last_return(minishell, "SUGAR", pid);
	last_return(minishell, "PANCAKE", pid);
}
