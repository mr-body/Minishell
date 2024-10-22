/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:20:52 by gkomba            #+#    #+#             */
/*   Updated: 2024/10/21 16:40:03 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	command_unset(char **prompt, int pipe)
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
		/*aqui*/
		while (environ[i])
		{
			/*aqui*/
			if (ft_strncmp(environ[i], prompt[line], name_len) == 0
				&& environ[i][name_len] == '=')
			{
				/*aqui*/
				j = i;
				/*aqui*/
				while (environ[j])
				{
					environ[j] = environ[j + 1]; /*aqui*/
					j++;
				}
			}
			i++;
		}
	}
	if (pipe)
		exit(0);
	return (0);
}
