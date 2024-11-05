/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:57:35 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/05 15:53:41 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_child_process_pipe(t_minishell *minishell, int i,
		int num_commands)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (!minishell->last)
		{
			if (minishell->is_redir == 1)
			{
				if (minishell->fd_type == 0)
					dup2(minishell->fd, STDOUT_FILENO);
				else if (minishell->fd_type == 1)
					dup2(minishell->fd, STDIN_FILENO);
			}
			else
			{
				if (i < num_commands - 1)
					dup2(minishell->pipe_fds[i * 2 + 1], STDOUT_FILENO);
				if (i > 0)
					dup2(minishell->pipe_fds[(i - 1) * 2], STDIN_FILENO);
				close_fds(minishell, num_commands);
			}
		}
		else
		{
			if (minishell->fd_type == 0)
				dup2(minishell->fd, STDOUT_FILENO);
			else if (minishell->fd_type == 1)
				dup2(minishell->fd, STDIN_FILENO);
				
			if (i < num_commands - 1)
				dup2(minishell->pipe_fds[i * 2 + 1], STDOUT_FILENO);
			if (i > 0)
				dup2(minishell->pipe_fds[(i - 1) * 2], STDIN_FILENO);
			close_fds(minishell, num_commands);
		}
		if (shell(minishell->args->args, 1, minishell) == -1)
		{
			perror("error: ");
			exit(1);
		}
	}
	else if (pid < 0)
		perror("fork error: ");
}

void	execute_child_process(t_minishell *minishell)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror("fork error: ");
	else if (pid == 0)
	{
		if (minishell->fd_type == 0)
			dup2(minishell->fd, STDOUT_FILENO);
		else
			dup2(minishell->fd, STDIN_FILENO);
		if (shell(minishell->args->args, 0, minishell) == -1)
		{
			ft_print_command_error(minishell->args->args[0]);
			exit(EXIT_FAILURE);
		}
		close(minishell->fd);
	}
	else
		waitpid(pid, &minishell->exit_status, 0);
}
