/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:20:32 by gkomba            #+#    #+#             */
/*   Updated: 2024/12/07 19:19:26 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_env_syntax(char **prompt, int pipe)
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
	return (0);
}

int	command_env(char **prompt, char **environ, int pipe, t_minishell *minishell)
{
	int		i;
	char	*variable;

	variable = NULL;
	if (check_env_syntax(prompt, pipe))
		return (ft_ctrl_c(1), 1);
	i = -1;
	while (environ[++i])
	{
		if (ft_strchr(environ[i], '='))
		{
			variable = quote_scanner(environ[i]);
			write(minishell->fd, environ[i], ft_strlen(environ[i]));
			write(minishell->fd, "\n", 1);
			free_ptr(variable);
		}
	}
	if (pipe)
	{
		ft_free_matriz(prompt);
		exit(0);
	}
	return (ft_ctrl_c(0), 0);
}
