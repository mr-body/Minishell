/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:23:19 by gkomba            #+#    #+#             */
/*   Updated: 2024/12/02 13:03:26 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	shell_builtin(char **prompt, char **environ, int pipe,
		t_minishell *minishell)
{
	if (ft_strncmp(prompt[0], "exit", 4) == 0)
		minishell->exit_status = command_exit(prompt, pipe, minishell);
	else if (ft_strncmp(prompt[0], "env", 3) == 0)
		minishell->exit_status = command_env(prompt, environ, pipe, minishell);
	else if (ft_strncmp(prompt[0], "cd", 2) == 0)
		minishell->exit_status = command_cd(prompt, minishell);
	else if (ft_strncmp(prompt[0], "echo", 4) == 0)
		minishell->exit_status = command_echo(prompt, pipe, minishell);
	else if (ft_strncmp(prompt[0], "pwd", 3) == 0)
		minishell->exit_status = command_pwd(prompt, pipe, minishell);
	else if (ft_strncmp(prompt[0], "export", 6) == 0)
		minishell->exit_status = command_export(prompt, pipe, minishell);
	else if (ft_strncmp(prompt[0], "unset", 6) == 0)
		minishell->exit_status = command_unset(prompt, pipe, minishell);
	return (minishell->exit_status);
}

char	*shell_binary(char **prompt)
{
	char	*cmd_path;
	char	**routes;
	int		i;

	routes = ft_split(getenv("PATH"), ':');
	if (routes == NULL || !validate_command(prompt[0]))
	{
		if (routes)
			routes = ft_free_matriz(routes);
		return (prompt[0]);
	}
	if (access(prompt[0], X_OK) == 0)
		cmd_path = prompt[0];
	else
	{
		i = -1;
		while (routes[++i] != NULL)
		{
			cmd_path = ft_strcat(routes[i], prompt[0], '/');
			if (access(cmd_path, X_OK) == 0)
				break ;
			cmd_path = free_ptr(cmd_path);
		}
	}
	return (return_cmd_path(cmd_path, routes));
}

int	shell(char **prompt, int pipe, t_minishell *minishell)
{
	extern char	**environ;
	char		*command;

	command = NULL;
	if (is_builtin(prompt[0]))
		return (shell_builtin(prompt, environ, pipe, minishell));
	else
	{
		command = shell_binary(prompt);
		if (command != NULL)
		{
			ft_delete_quotes_on_matriz(prompt);
			return (execve(command, prompt, environ));
		}
		command = free_ptr(command);
	}
	return (-1);
}

void	clean(t_minishell *minishell)
{
	if (minishell->args)
		free_data(minishell->args);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	return (0);
}
