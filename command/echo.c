/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:20:39 by gkomba            #+#    #+#             */
/*   Updated: 2024/10/19 16:22:24 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	command_echo(char **prompt, int pipe)
{
	int	i;

	i = 0;
	while (prompt[++i])
	{
		write(1, prompt[i], ft_strlen(prompt[i]));
		write(1, " ", 1);
	}
	write(1, "\n", 1);
	if (pipe)
	{
		ft_free_matriz(prompt);
		exit(0);
	}
	return (0);
}
