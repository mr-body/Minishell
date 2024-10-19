/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sheel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:23:19 by gkomba            #+#    #+#             */
/*   Updated: 2024/10/19 16:38:09 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*funcao que executa os builtins*/
int	shell_builtin(char **prompt, char **environ, int pipe)
{
	int	exit_status;

	exit_status = 0;
	if (ft_strncmp(prompt[0], "exit", 4) == 0)
	{
		prompt = ft_free_matriz(prompt);
		exit(0);
	}
	else if (ft_strncmp(prompt[0], "env", 3) == 0)
		exit_status = command_env(prompt, environ);
	else if (ft_strncmp(prompt[0], "cd", 2) == 0)
		exit_status = command_cd(prompt);
	else if (ft_strncmp(prompt[0], "echo", 4) == 0)
		exit_status = command_echo(prompt, pipe);
	else if (ft_strncmp(prompt[0], "pwd", 3) == 0)
		exit_status = command_pwd(prompt, pipe);
    else if (ft_strncmp(prompt[0], "export", 6) == 0)
		exit_status = command_export(prompt, pipe);
	return (exit_status);
}

/*funcao que pega o caminho dos bainarios*/
char	*shell_binary(char **prompt, char **environ)
{
	char	*cmd_path;
	char	**routes;
	int		i;

	routes = ft_split(getenv("PATH"), ':');
	if (access(prompt[0], X_OK) == 0)
		cmd_path = prompt[0];
	else
	{
		i = -1;
		while (routes[++i])
		{
			cmd_path = ft_strcat(routes[i], prompt[0], '/');
			if (access(cmd_path, X_OK) == 0)
				break ;
			cmd_path = free_ptr(cmd_path);
		}
	}
	if (cmd_path == NULL)
	{
		routes = ft_free_matriz(routes);
		return (NULL);
	}
	routes = ft_free_matriz(routes);
	return (cmd_path);
}

/*funcao que chama a funcao de xecutar builtin e a funcao*/
/*de pegar o caminho do binario*/
int	shell(char **prompt, int pipe)
{
	extern char	**environ;
	char		*command;

	command = NULL;
	if (is_builtin(prompt[0]))
		return (shell_builtin(prompt, environ, pipe));
	else
	{
		command = shell_binary(prompt, environ);
		execve(command, prompt, environ);
		command = free_ptr(command);
	}
	return (-1);
}

/*funcao que verifica se um comando é um builtin*/
int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "exit", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
    else if (ft_strncmp(cmd, "export", 6) == 0)
		return (1);
	return (0);
}
