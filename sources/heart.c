/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heart.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:02:16 by waalexan          #+#    #+#             */
/*   Updated: 2024/11/22 15:57:13 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_command(t_minishell *minishell)
{
	int	redir;
	int	retrn;

	redir = 0;
	if (extract_command(minishell, &redir, &retrn) != 0)
		return (retrn);
	if (redir == R_TRUNC_O)
		redir_trunc_o(minishell, 0);
	else if (redir == R_APPEND_O)
		redir_append_o(minishell, 0);
	else if (redir == R_TRUNC_I)
		redir_trunc_in(minishell, 0);
	else if (redir == R_APPEND_I)
		redir_append_in(minishell, 0);
	if (!minishell->args || minishell->not_flag == -1)
		return (free_data(minishell->args), minishell->not_flag = 0, 0);
	if (!is_builtin(minishell->args->args[0]))
		execute_child_process(minishell);
	else
	{
		if (shell(minishell->args->args, 0, minishell) == -1)
			ft_print_command_error(minishell->args->args[0]);
	}
	clean(minishell);
	return (0);
}

int	exec_command_pipe(t_minishell *minishell)
{
	int		num_commands;
	int		fd[2];
	int		prev_fd;
	int		in_fd;
	int		out_fd;
	int		i;
	t_heart	var;
	pid_t	pid;

	minishell->raw_args = ft_big_split(minishell->command, '|');
	num_commands = ft_matriz_len(minishell->raw_args->args);
	i = -1;
	prev_fd = 0;
	in_fd = 0;
	out_fd = 0;
	while (++i < num_commands)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			if (i > 0)
				in_fd = prev_fd;
			else
				in_fd = 0;
			if (i < num_commands - 1)
				out_fd = fd[1];
			else
				out_fd = 1;
			close(fd[0]);
			if (in_fd != 0)
			{
				dup2(in_fd, STDIN_FILENO);
				close(in_fd);
			}
			if (out_fd != 1)
			{
				dup2(out_fd, STDOUT_FILENO);
				close(out_fd);
			}
			minishell->is_redir = 0;
			minishell->args = net_args(minishell->raw_args->args[i]);
			var.redir = is_redir(minishell->raw_args->args[i]);
			minishell->redirect_command = minishell->raw_args->args[i];
			if (var.redir == R_TRUNC_O)
				redir_trunc_o(minishell, 1);
			else if (var.redir == R_APPEND_O)
				redir_append_o(minishell, 1);
			else if (var.redir == R_TRUNC_I)
				redir_trunc_in(minishell, 1);
			else if (var.redir == R_APPEND_I)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				redir_append_in(minishell, 1);
			}
			if (!minishell->args || minishell->not_flag == -1)
			{
				exit(130);
				free_data(minishell->args);
			}
			if (shell(minishell->args->args, 1, minishell) == -1)
			{
				ft_print_command_error(minishell->args->args[0]);
				free_data(minishell->args);
				exit(127);
			}
			free_data(minishell->args);
		}
		else
		{
			close(fd[1]);
			if (prev_fd > 0)
				close(prev_fd);
			prev_fd = fd[0];
			waitpid(pid, &minishell->exit_status, 0);
			last_return(minishell, "SUGAR", pid);
			last_return(minishell, "PANCAKE", pid);
		}
	}
	free_data(minishell->raw_args);
	return (0);
}

int	whitespace_and_syntax(t_minishell *minishell, char **data)
{
	if (minishell->readline[0] == '\n' || minishell->readline[0] == '\0' || minishell->readline[0] == '\t')
		return (ft_free_matriz(data), 1);
	if (syntax_checker(minishell) == 2)
		return (ft_free_matriz(data), 2);
	return (0);
}

int	execute_command(t_minishell *minishell)
{
	char	**data;

	minishell->fd = STDOUT_FILENO;
	minishell->fd_type = 1;
	if (unclosed_quotes(minishell->readline) == 1)
		return (1);
	data = ft_split_ms(minishell->readline, ' ');
	if (data[0] == NULL)
		return (ft_free_matriz(data), 0);
	minishell->command = minishell->readline;
	minishell->redirect_command = minishell->readline;
	if (whitespace_and_syntax(minishell, data) != 0)
		return (0);
	if (check_if_str_is_pipe(data) == 1)
	{
		ft_free_matriz(data);
		minishell->exit_status = exec_command_pipe(minishell);
	}
	else
	{
		ft_free_matriz(data);
		minishell->exit_status = exec_command(minishell);
	}
	return (0);
}
