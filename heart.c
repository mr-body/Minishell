/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heart.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:19:40 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/04 19:04:18 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(t_minishell *minishell)
{
	pid_t	pid;
	int		redir;

	minishell->args = net_args(minishell->command);
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
		{
			perror("fork error: ");
		}
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
			exit(EXIT_SUCCESS);
		}
		else
		{
			waitpid(pid, &minishell->exit_status, 0);
			ft_free_matriz(minishell->args);
		}
	}
	else
	{
		if (shell(minishell->args, 0, minishell) == -1)
		{
			ft_print_command_error(minishell->args[0]);
		}
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
		printf("=====================================\n");
		ft_print_matriz(minishell->args);
		printf("=====================================\n");
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

void	exec_command_pipe(t_minishell *minishell)
{
	int		num_commands;
	int		i;
	pid_t	pid;
	int		redir;

	minishell->raw_args = ft_split_ms(minishell->command, '|');
	printf("=====================================\n");
	ft_print_matriz(minishell->raw_args);
	printf("=====================================\n");
	num_commands = ft_matriz_len(minishell->raw_args);
	printf("=====================================\n");
	printf("num_commands: %d\n", num_commands);
	printf("=====================================\n");
	minishell->pipe_fds = (int *)malloc(sizeof(int) * (2 * num_commands - 1));
	open_fds(minishell, num_commands);
	if (exec_command_pipe_aux(minishell, num_commands))
		return ;
	ft_exit_process(minishell, num_commands);
}

int		check_if_str_is_pipe(char **matriz);

void	execute_command(t_minishell *minishell)
{
	char	**commands;
	char	**data;

	minishell->fd = STDOUT_FILENO;
	minishell->fd_type = 1;
	data = net_args(minishell->readline);
	printf("=====================================\n");
	ft_print_matriz(data);
	printf("=====================================\n");
	minishell->command = minishell->readline;
	if (minishell->readline[0] == '\n' || minishell->readline[0] == '\0')
	{
		ft_free_matriz(data);
		return ;
	}
	if (check_if_str_is_pipe(data) == 1)
	{
		ft_free_matriz(data);
		exec_command_pipe(minishell);
	}
	else
	{
		ft_free_matriz(data);
		exec_command(minishell);
	}
}

int	check_if_str_is_pipe(char **matriz)
{
	int	i;

	i = 0;
	while (matriz[i])
	{
		if (ft_strncmp(matriz[i], "|", ft_strlen(matriz[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}
