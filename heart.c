/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heart.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:19:40 by gkomba            #+#    #+#             */
/*   Updated: 2024/10/19 16:19:51 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*funcao que executa os comandos simples*/
void	exec_command(t_minishell *minishell)
{
	int		exit_status;
	pid_t	pid;

	minishell->args = net_args(minishell->readline);
	if (!is_builtin(minishell->args[0]))
	{
		pid = fork();
		if (pid < 0)
			perror("fork error: ");
		else if (pid == 0)
		{
			if (shell(minishell->args, 0) == -1)
			{
				ft_print_command_error(minishell->args[0]);
				exit(EXIT_FAILURE);
			}
		}
		else
			waitpid(pid, &minishell->exit_status, 0);
	}
	else
	{
		if (shell(minishell->args, 0) == -1)
			perror("error: ");
	}
	ft_free_matriz(minishell->args);
}

/*funcao que executa os comandos quando tem pipes*/
void	exec_command_pipe(t_minishell *minishell)
{
	int		num_commands;
	int		i;
	pid_t	pid;

	minishell->raw_args = ft_split(minishell->readline, '|');
	num_commands = ft_matriz_len(minishell->raw_args);
	minishell->pipe_fds = (int *)malloc(sizeof(int) * (2 * num_commands - 1));
	open_fds(minishell, num_commands);
	i = -1;
	while (++i < num_commands)
	{
		minishell->args = net_args(minishell->raw_args[i]);
		pid = fork();
		if (pid == 0)
		{
			if (i < num_commands - 1)
				dup2(minishell->pipe_fds[i * 2 + 1], STDOUT_FILENO);
			if (i > 0)
				dup2(minishell->pipe_fds[(i - 1) * 2], STDIN_FILENO);
			close_fds(minishell, num_commands);
			if (shell(minishell->args, 1) == -1)
			{
				perror("error: ");
				exit(1);
			}
		}
		else if (pid < 0)
			perror("fork error: ");
		ft_free_matriz(minishell->args);
	}
	ft_exit_process(minishell, num_commands);
}

/*funcao que chama as funcao que vao exeutar os comandos*/
void	execute_command(t_minishell *minishell)
{
	if (strchr(minishell->readline, '|'))
		exec_command_pipe(minishell);
	else
		exec_command(minishell);
}
