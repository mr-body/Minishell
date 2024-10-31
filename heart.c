/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heart.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:19:40 by gkomba            #+#    #+#             */
/*   Updated: 2024/10/31 09:02:34 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*funcao que executa os comandos simples*/
void	exec_command(t_minishell *minishell)
{
	int		exit_status;
	pid_t	pid;

	minishell->args = net_args(minishell->command);
	if (!minishell->args)
	{
		ft_free_matriz(minishell->args);
		return ;
	}
	if (!minishell->args[0])
		return ;
	if (!is_builtin(minishell->args[0]))
	{
		pid = fork();
		if (pid < 0)
			perror("fork error: ");
		else if (pid == 0)
		{
			if (minishell->fd_type == 0)
				dup2(minishell->fd, STDOUT_FILENO);
			else
				dup2(minishell->fd, STDIN_FILENO);
			if (shell(minishell->args, 0, minishell) == -1)
			{
				ft_print_command_error(minishell->args[0]);
				exit(EXIT_FAILURE);
			}
			close(minishell->fd);
		}
		else
			waitpid(pid, &minishell->exit_status, 0);
	}
	else
	{
		if (shell(minishell->args, 0, minishell) == -1)
			ft_print_command_error(minishell->args[0]);
	}
	ft_free_matriz(minishell->args);
}

/*funcao que executa os comandos quando tem pipes*/
void	exec_command_pipe(t_minishell *minishell)
{
	int		num_commands;
	int		i;
	pid_t	pid;

	minishell->raw_args = ft_split(minishell->command, '|');
	num_commands = ft_matriz_len(minishell->raw_args);
	minishell->pipe_fds = (int *)malloc(sizeof(int) * (2 * num_commands - 1));
	open_fds(minishell, num_commands);
	i = -1;
	while (++i < num_commands)
	{
		minishell->args = net_args(minishell->raw_args[i]);
		if (!minishell->args)
		{
			ft_exit_process(minishell, num_commands);
			return ;
		}
		if (!minishell->args)
			return ;
		pid = fork();
		if (pid == 0)
		{
			if (minishell->fd_type == 0)
				dup2(minishell->fd, STDOUT_FILENO);
			else
				dup2(minishell->fd, STDIN_FILENO);
			if (i < num_commands - 1)
				dup2(minishell->pipe_fds[i * 2 + 1], STDOUT_FILENO);
			if (i > 0)
				dup2(minishell->pipe_fds[(i - 1) * 2], STDIN_FILENO);
			close_fds(minishell, num_commands);
			if (shell(minishell->args, 1, minishell) == -1)
			{
				perror("error: ");
				exit(1);
			}
			close(minishell->fd);
		}
		else if (pid < 0)
			perror("fork error: ");
		ft_free_matriz(minishell->args);
	}
	ft_exit_process(minishell, num_commands);
}

// Função que executa o comando
void	execute_command(t_minishell *minishell)
{
	int		redir;
	int		fd;

	minishell->fd = 1;
	minishell->fd_type = 1;
	redir = is_redir(minishell->readline);
	if (redir == R_TRUNC_O)
		redir_trunc_o(minishell);
	else if (redir == R_APPEND_O)
		redir_append_o(minishell);
	else if (redir == R_TRUNC_I)
		redir_trunc_in(minishell);
	else if (redir == R_APPEND_I)
		redir_append_in(minishell);
	else
	{
		minishell->command = minishell->readline;
		if (strchr(minishell->command, '|'))
			exec_command_pipe(minishell);
		else
			exec_command(minishell);
	}
}
