/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heart.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:19:40 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/03 11:31:17 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*funcao que executa os comandos simples*/
void	exec_command(t_minishell *minishell)
{
	int		exit_status;
	pid_t	pid;
	int		redir;
	int		fd;

	if (minishell->args)
		ft_free_matriz(minishell->args);
	minishell->args = net_args(minishell->command);
	if (!minishell->args)
	{
		//ft_free_matriz(minishell->args);
		return ;
	}
	if (!minishell->args[0])
		return ;
	redir = is_redir(minishell->command);
	minishell->redirect_command = minishell->command;
	if (redir == R_TRUNC_O)
		redir_trunc_o(minishell);
	else if (redir == R_APPEND_O)
		redir_append_o(minishell);
	else if (redir == R_TRUNC_I)
		redir_trunc_in(minishell);
	else if (redir == R_APPEND_I)
		redir_append_in(minishell);
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
			ft_free_matriz(minishell->args);
		}
		else
			waitpid(pid, &minishell->exit_status, 0);
	}
	else
	{
		if (shell(minishell->args, 0, minishell) == -1)
			ft_print_command_error(minishell->args[0]);
		ft_free_matriz(minishell->args);
	}
}

int	exec_command_pipe_aux(t_minishell *minishell, int num_commands)
{
	int	i;
	int	redir;

	i = -1;
	while (++i < num_commands)
	{
		minishell->is_redir = 0;
		minishell->fd = STDOUT_FILENO;
		minishell->fd_type = 1;
		minishell->args = net_args(minishell->raw_args[i]);
		redir = is_redir(minishell->raw_args[i]);
		minishell->redirect_command = minishell->raw_args[i];
		if (redir == R_TRUNC_O)
			redir_trunc_o(minishell);
		else if (redir == R_APPEND_O)
			redir_append_o(minishell);
		else if (redir == R_TRUNC_I)
			redir_trunc_in(minishell);
		else if (redir == R_APPEND_I)
			redir_append_in(minishell);
		if (!minishell->args)
			return (ft_exit_process(minishell, num_commands), 1);
		execute_child_process_pipe(minishell, i, num_commands);
		ft_free_matriz(minishell->args);
		minishell->fd = 1;
	}
	return (0);
}

/*funcao que executa os comandos quando tem pipes*/
void	exec_command_pipe(t_minishell *minishell)
{
	int		num_commands;
	int		i;
	pid_t	pid;
	int		redir;

	minishell->raw_args = ft_split(minishell->command, '|');
	num_commands = ft_matriz_len(minishell->raw_args);
	minishell->pipe_fds = (int *)malloc(sizeof(int) * (2 * num_commands - 1));
	open_fds(minishell, num_commands);
	if (exec_command_pipe_aux(minishell, num_commands))
		return ;
	ft_exit_process(minishell, num_commands);
}

// Função que executa o comando
void	execute_command(t_minishell *minishell)
{
	char **commands;

	minishell->fd = STDOUT_FILENO;
	minishell->fd_type = 1;

	minishell->command = minishell->readline;
	if(unbalanced_quotes(minishell->readline))
		return ;
	if (strchr(minishell->readline, '|'))
		exec_command_pipe(minishell);
	else
		exec_command(minishell);

}