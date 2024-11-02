/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heart.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:19:40 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/01 16:00:37 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(t_minishell *minishell)
{
	int		exit_status;

	minishell->args = net_args(minishell->command);
	if (!minishell->args)
	{
		ft_free_matriz(minishell->args);
		return ;
	}
	if (!minishell->args[0])
		return ;
	if (!is_builtin(minishell->args[0]))
		execute_child_process(minishell);
	else
	{
		if (shell(minishell->args, 0, minishell) == -1)
			ft_print_command_error(minishell->args[0]);
	}
	ft_free_matriz(minishell->args);
}

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
		execute_child_process_pipe(minishell, i, num_commands);
		ft_free_matriz(minishell->args);
	}
	ft_exit_process(minishell, num_commands);
}

void	execute_command(t_minishell *minishell)
{
	int	redir;
	int	fd;

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
