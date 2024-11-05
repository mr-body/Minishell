/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heart.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:19:40 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/05 16:08:04 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct heart
{
	int	i;
	int	redir;
}	t_heart;

int	exec_command_pipe_aux(t_minishell *minishell, int num_commands)
{
	t_heart	var;

	var.i = -1;
	while (++var.i < num_commands)
	{
		minishell->is_redir = 0;
		minishell->args = net_args(minishell->raw_args->args[var.i]);
		var.redir = is_redir(minishell->raw_args->args[var.i]);
		minishell->redirect_command = minishell->raw_args->args[var.i];
		if (var.redir == R_TRUNC_O)
			redir_trunc_o(minishell);
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

/*funcao que executa os comandos quando tem pipes*/
void	exec_command_pipe(t_minishell *minishell)
{
	int		num_commands;
	int		i;
	pid_t	pid;
	int		redir;

	minishell->verify_pipes_syntax = ft_split_ms(minishell->command, '|');
	if (verify_pipes_syntax(minishell))
		return ;
	minishell->raw_args = ft_big_split(minishell->command, '|');
	num_commands = ft_matriz_len(minishell->raw_args->args);
	minishell->pipe_fds = (int *)malloc(sizeof(int) * (2 * num_commands - 1));
	open_fds(minishell, num_commands);
	if (exec_command_pipe_aux(minishell, num_commands))
		return ;
	ft_exit_process(minishell, num_commands);
}

/* Função que executa o comando */
void	execute_command(t_minishell *minishell)
{
	char	**commands;

	minishell->fd = STDOUT_FILENO;
	minishell->fd_type = 1;
	minishell->command = minishell->readline;
	exec_command_pipe(minishell);
}
