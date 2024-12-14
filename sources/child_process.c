/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:57:35 by gkomba            #+#    #+#             */
/*   Updated: 2024/12/14 23:00:25 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	send_to_execute_child(t_minishell *ms)
{
	if (is_avaliable_on_path(ms->args->args) == 0)
	{
		ms->exit = ft_print_command_error(ms->args->args[0]);
		exit(ms->exit);
	}
	else
	{
		if (shell(ms->args->args, 0, ms) == -1)
		{
			ms->exit = ft_print_command_error(ms->args->args[0]);
			exit(ms->exit);
		}
	}
}

void	execute_child_process(t_minishell *ms)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror("fork error: ");
	else if (pid == 0)
	{
		verif_redir(ms);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (ms->fd_type == 0)
			dup2(ms->fd, STDOUT_FILENO);
		else
			dup2(ms->fd, STDIN_FILENO);
		send_to_execute_child(ms);
		close(ms->fd);
	}
	else
		last_return(ms, "SUGAR", pid);
	last_return(ms, "PANCAKE", pid);
}

int	is_avaliable_on_path(char **prompt)
{
	char	*command;
	char	*tmp;
	char	**tmp_matriz;

	tmp_matriz = ft_matdup(prompt);
	command = NULL;
	tmp = NULL;
	ft_delete_quotes_on_matriz(tmp_matriz);
	if (ft_strlen(tmp_matriz[0]) == 0)
	{
		ft_free_matriz(tmp_matriz);
		tmp = prompt[0];
		prompt[0] = ft_strdup("''");
		tmp = free_ptr(tmp);
		return (0);
	}
	command = shell_binary(tmp_matriz);
	if (command != NULL)
	{
		ft_free_matriz(tmp_matriz);
		return (1);
	}
	ft_free_matriz(tmp_matriz);
	return (0);
}

char	*return_cmd_path(char *cmd_path, char **routes)
{
	if (cmd_path == NULL)
		return (ft_free_matriz(routes), NULL);
	routes = ft_free_matriz(routes);
	return (cmd_path);
}
