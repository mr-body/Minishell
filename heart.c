/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heart.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:19:40 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/06 18:29:26 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_command(t_minishell *minishell)
{
	int	redir;
	int	retrn;

	redir = 0;
	if (extract_command(minishell, &redir, &retrn) != 0)
		return (retrn);
	if (redir == R_TRUNC_O)
		redir_trunc_o(minishell);
	else if (redir == R_APPEND_O)
		redir_append_o(minishell);
	else if (redir == R_TRUNC_I)
		redir_trunc_in(minishell);
	else if (redir == R_APPEND_I)
		redir_append_in(minishell);
	if (!minishell->args)
		return (0);
	if (!is_builtin(minishell->args->args[0]))
		execute_child_process(minishell);
	else
	{
		if (shell(minishell->args->args, 0, minishell) == -1)
			ft_print_command_error(minishell->args->args[0]);
	}
	free_data(minishell->args);
	return (0);
}

int	exec_command_pipe_aux(t_minishell *minishell, int num_commands)
{
	t_heart	var;

	var.i = -1;
	var.redir = 0;
	last_redir(minishell);
	while (++var.i < num_commands)
	{
		minishell->args = net_args(minishell->raw_args->args[var.i]);
		var.redir = is_redir(minishell->raw_args->args[var.i]);
		minishell->redirect_command = minishell->raw_args->args[var.i];
		if (var.redir == R_TRUNC_O)
			minishell->status = redir_trunc_o(minishell);
		else if (var.redir == R_APPEND_O)
			redir_append_o(minishell);
		else if (var.redir == R_TRUNC_I)
			redir_trunc_in(minishell);
		else if (var.redir == R_APPEND_I)
			redir_append_in(minishell);
		if (!minishell->args)
			return (ft_exit_process(minishell, num_commands), 1);
		execute_child_process_pipe(minishell, var.i, num_commands);
		free_data(minishell->args);
		minishell->fd = 1;
	}
	return (0);
}

int	exec_command_pipe(t_minishell *minishell)
{
	int		num_commands;
	int		i;
	pid_t	pid;
	int		redir;

	minishell->raw_args = ft_big_split(minishell->command, '|');
	num_commands = ft_matriz_len(minishell->raw_args->args);
	minishell->pipe_fds = (int *)malloc(sizeof(int) * (2 * num_commands - 1));
	open_fds(minishell, num_commands);
	if (exec_command_pipe_aux(minishell, num_commands))
		return (1);
	ft_exit_process(minishell, num_commands);
	return (0);
}

int	execute_command(t_minishell *minishell)
{
	char	**data;

	minishell->fd = STDOUT_FILENO;
	minishell->fd_type = 1;
	data = ft_split_ms(minishell->readline, ' ');
	if (data[0] == NULL)
		return (ft_free_matriz(data), 0);
	minishell->command = minishell->readline;
	minishell->status = 0;
	minishell->exit_status = 0;
	minishell->redirect_command = minishell->readline;
	if (minishell->readline[0] == '\n' || minishell->readline[0] == '\0')
		return (ft_free_matriz(data), 0);
	if (syntax_checker(minishell) == 2)
		return (ft_free_matriz(data), 1);
	if (check_if_str_is_pipe(data) == 1)
	{
		ft_free_matriz(data);
		exec_command_pipe(minishell);
	}
	else
	{
		ft_free_matriz(data);
		minishell->exit_status = exec_command(minishell);
	}
}
