/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:20:32 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/06 18:14:32 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_env_syntax(char **prompt, int pipe)
{
	if (prompt[1])
	{
		if (pipe)
		{
			ft_free_matriz(prompt);
			exit(1);
		}
		return (ft_putendl_fd("env: too many arguments", 2), 1);
	}
}

int	command_env(char **prompt, char **environ, int pipe, t_minishell *minishell)
{
	int	i;

	if (check_env_syntax(prompt, pipe))
		return (1);
	i = -1;
	while (environ[++i])
	{
		if (ft_strchr(environ[i], '='))
		{
			write(minishell->fd, environ[i], ft_strlen(environ[i]));
			write(minishell->fd, "\n", 1);
		}
	}
	if (pipe)
	{
		ft_free_matriz(prompt);
		exit(0);
	}
	return (0);
}
