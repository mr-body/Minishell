/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:05:18 by gkomba            #+#    #+#             */
/*   Updated: 2024/10/31 12:21:20 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	increment_shell_level(t_minishell *minishell)
{
	char	**prompt;
	char	*shell_level;
	char	*name;
	int		level;

	shell_level = getenv("SHLVL");
	name = NULL;
	prompt = (char **)malloc(sizeof(char *) * 3);
	ft_memset(prompt, 0, sizeof(char *) * 3);
	prompt[0] = "export";
	prompt[2] = 0;
	if (shell_level)
	{
		name = "SHLVL=";
		level = ft_atoi(shell_level);
		level++;
		shell_level = ft_itoa(level);
		name = ft_strjoin(name, shell_level);
		prompt[1] = name;
		command_export(prompt, 0, minishell);
		free(shell_level);
		free(name);
	}
	else
	{
		name = "SHLVL=1";
		prompt[1] = name;
		command_export(prompt, 0, minishell);
	}
	free(prompt);
}

void	change_pwd(char *curr_pwd, t_minishell *minishell)
{
	char	**prompt;
	char	*name;

	prompt = (char **)malloc(sizeof(char *) * 3);
	ft_memset(prompt, 0, sizeof(char *) * 3);
	prompt[0] = "export";
	prompt[2] = 0;
	name = ft_strjoin("PWD=", curr_pwd);
	prompt[1] = name;
	command_export(prompt, 0, minishell);
	free(name);
	free(prompt);
}

void	change_old_pwd(char *old_pwd, t_minishell *minishell)
{
	char	**prompt;
	char	*name;

	prompt = (char **)malloc(sizeof(char *) * 3);
	ft_memset(prompt, 0, sizeof(char *) * 3);
	prompt[0] = "export";
	prompt[2] = 0;
	name = ft_strjoin("OLDPWD=", old_pwd);
	prompt[1] = name;
	command_export(prompt, 0, minishell);
	free(name);
	free(prompt);
}
