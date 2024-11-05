/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:20:52 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/05 14:59:46 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

typedef struct unset
{
	int		i;
	int		j;
	int		line;
	size_t	name_len;

}			t_unset;

int	command_unset(char **prompt, int pipe, t_minishell *minishell)
{
	extern char	**environ;
	t_unset		var;

	ft_memset(&var, 0, sizeof(t_unset));
	if (!prompt[1])
		return (ft_putstr_fd("Nome da variável não fornecido.\n", 1), -1);
	var.line = 0;
	while (prompt[++var.line])
	{
		var.name_len = strlen(prompt[var.line]);
		var.i = 0;
		while (environ[var.i])
		{
			if (strncmp(environ[var.i], prompt[var.line], var.name_len) == 0)
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
	if (pipe)
		exit(0);
	return (0);
}
