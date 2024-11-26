/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heart.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:02:16 by waalexan          #+#    #+#             */
/*   Updated: 2024/11/26 15:39:21 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_command(t_minishell *minishell)
{
	if (!is_builtin(minishell->args->args[0]))
		execute_child_process(minishell);
	else
	{
		verif_redir(minishell);
		if (shell(minishell->args->args, 0, minishell) == -1)
			ft_print_command_error(minishell->args->args[0]);
	}
	return (clean(minishell), 0);
}

static void	pipe_opt_one(t_minishell *minishell, t_pipe_data *var,
t_heart *var_header)
{
	if (var->i > 0)
		var->in_fd = var->prev_fd;
	else
		var->in_fd = 0;
	if (var->i < var->num_commands - 1)
		var->out_fd = var->fd[1];
	else
		var->out_fd = 1;
	close(var->fd[0]);
	if (var->in_fd != 0)
	{
		dup2(var->in_fd, STDIN_FILENO);
		close(var->in_fd);
	}
	if (var->out_fd != 1)
	{
		dup2(var->out_fd, STDOUT_FILENO);
		close(var->out_fd);
	}
	minishell->is_redir = 0;
	minishell->args = net_args(minishell->raw_args->args[var->i]);
	var_header->redir = is_redir(minishell->raw_args->args[var->i]);
	minishell->redirect_command = minishell->raw_args->args[var->i];
}

static void	pipe_opt_two(t_minishell *minishell, t_heart *var_header)
{
	if (var_header->redir == R_TRUNC_O)
		redir_trunc_o(minishell, 1);
	else if (var_header->redir == R_APPEND_O)
		redir_append_o(minishell, 1);
	else if (var_header->redir == R_TRUNC_I)
		redir_trunc_in(minishell, 1);
	else if (var_header->redir == R_APPEND_I)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		redir_append_in(minishell, 1);
	}
	if (!minishell->args || minishell->not_flag == -1)
		exit(130);
	if (shell(minishell->args->args, 1, minishell) == -1)
	{
		ft_print_command_error(minishell->args->args[0]);
		free_data(minishell->args);
		exit(127);
	}
	free_data(minishell->args);
}

static void	pipe_opt_three(t_minishell *minishell, t_pipe_data *var)
{
	close(var->fd[1]);
	if (var->prev_fd > 0)
		close(var->prev_fd);
	var->prev_fd = var->fd[0];
	waitpid(var->pid, &minishell->exit_status, 0);
	last_return(minishell, "SUGAR", var->pid);
	last_return(minishell, "PANCAKE", var->pid);
}

int	exec_command_pipe(t_minishell *minishell)
{
	t_pipe_data	var;
	t_heart		var_header;

	minishell->raw_args = ft_big_split(minishell->command, '|');
	var.num_commands = ft_matriz_len(minishell->raw_args->args);
	var.i = -1;
	var.prev_fd = 0;
	var.in_fd = 0;
	var.out_fd = 0;
	while (++var.i < var.num_commands)
	{
		pipe(var.fd);
		var.pid = fork();
		if (var.pid == 0)
		{
			pipe_opt_one(minishell, &var, &var_header);
			pipe_opt_two(minishell, &var_header);
		}
		else
			pipe_opt_three(minishell, &var);
	}
	free_data(minishell->raw_args);
	return (0);
}
