/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:20:52 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/10 16:45:41 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	unset_var(char **prpt)
{
	t_unset		var;
	extern char	**environ;

	ft_memset(&var, 0, sizeof(t_unset));
	var.line = 0;
	while (prpt[++var.line])
	{
		var.name_len = ft_strlen(prpt[var.line]);
		var.i = 0;
		while (environ[var.i])
		{
			if (ft_strncmp(environ[var.i], prpt[var.line], var.name_len) == 0)
			{
				while (environ[var.i])
				{
					environ[var.i] = environ[var.i + 1];
					var.i++;
				}
				break ;
			}
			var.i++;
		}
	}
}

int	command_unset(char **prompt, int pipe, t_minishell *minishell)
{
	if (!prompt[1])
	{
		ft_ctrl_c(1);
		return (1);
	}
	unset_var(prompt);
	if (pipe)
	{
		minishell->process_out = 0;
		exit(0);
	}
	ft_ctrl_c(0);
	return (0);
}
