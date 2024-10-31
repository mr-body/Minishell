/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:20:52 by gkomba            #+#    #+#             */
/*   Updated: 2024/10/31 07:25:44 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	command_unset(char **prompt, int pipe, t_minishell *minishell)
{
	extern char	**environ;
	int			i;
	int			j;
	int			line;
	size_t		name_len;

	if (!prompt[1])
	{
		ft_putstr_fd("Nome da variável não fornecido.\n", 1);
		return (-1);
	}
	line = 0;
	while (prompt[++line])
	{
		name_len = strlen(prompt[line]);
		i = 0;
		while (environ[i])
		{
			if (strncmp(environ[i], prompt[line], name_len) == 0)
			{
				while (environ[i])
				{
					environ[i] = environ[i + 1];
					i++;
				}
				break;
			}
			i++;
		}
	}
	if (pipe)
		exit(0);
	return (0);
}
