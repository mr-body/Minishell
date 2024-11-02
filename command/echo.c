/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:20:39 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/02 17:41:54 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **space_case(char **prompt)
{
	
}

int	command_echo(char **prompt, int pipe, t_minishell *minishell)
{
	int	i;


	i = 0;
	while (prompt[++i])
	{
		write(minishell->fd, prompt[i], ft_strlen(prompt[i]));
		write(minishell->fd, " ", 1);
	}
	write(1, "\n", 1);
	if (pipe)
	{
		ft_free_matriz(prompt);
		exit(0);
	}
	return (0);
}
