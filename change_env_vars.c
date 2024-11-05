/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:05:18 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/05 04:19:27 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct increment_shell_level
{
	char	*prompt[3];
	char	*shell_level;
	char	*name;
	int		level;
}			t_increment_shell_level;

void	increment_shell_level(t_minishell *minishell)
{
	t_increment_shell_level	var;

	var.shell_level = getenv("SHLVL");
	var.prompt[0] = "export";
	var.prompt[2] = NULL;
	if (var.shell_level)
	{
		var.level = ft_atoi(var.shell_level);
		var.level++;
		var.shell_level = ft_itoa(var.level);
		var.name = ft_strjoin("SHLVL=", var.shell_level);
		var.prompt[1] = var.name;
		command_export(var.prompt, 0, minishell);
		free(var.shell_level);
		free(var.name);
	}
	else
	{
		var.name = "SHLVL=1";
		var.prompt[1] = var.name;
		command_export(var.prompt, 0, minishell);
	}
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
