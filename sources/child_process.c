/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:57:35 by gkomba            #+#    #+#             */
/*   Updated: 2024/12/11 18:40:54 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_child_process(t_minishell *minishell)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror("fork error: ");
	else if (pid == 0)
	{
		verif_redir(minishell);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (minishell->fd_type == 0)
			dup2(minishell->fd, STDOUT_FILENO);
		else
			dup2(minishell->fd, STDIN_FILENO);
		if (is_avaliable_on_path(minishell->args->args) == 0)
		{
			minishell->exit = ft_print_command_error(minishell->args->args[0]);
			exit(minishell->exit);
		}
		else
		{
			if (shell(minishell->args->args, 0, minishell) == -1)
			{
				minishell->exit = ft_print_command_error(minishell->args->args[0]);
				exit(minishell->exit);
			}
		}
		close(minishell->fd);
	}
	else
		last_return(minishell, "SUGAR", pid);
	last_return(minishell, "PANCAKE", pid);
}

int	is_avaliable_on_path(char **prompt)
{
	char	*command;
	char	*tmp;

	command = NULL;
	tmp = NULL;
	ft_delete_quotes_on_matriz(prompt);
	if (ft_strlen(prompt[0]) == 0)
	{
		tmp = prompt[0];
		prompt[0] = ft_strdup("''");
		tmp = free_ptr(tmp);
		return (0);
	}
	command = shell_binary(prompt);
	if (command != NULL)
	{
		command = free_ptr(command);
		return (1);
	}
	return (0);
}

char	*return_cmd_path(char *cmd_path, char **routes)
{
	if (cmd_path == NULL)
		return (ft_free_matriz(routes), NULL);
	routes = ft_free_matriz(routes);
	return (cmd_path);
}
