/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:20:18 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/05 14:59:48 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	command_pwd(char **prompt, int pipe, t_minishell *minishell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("getcwd error");
		exit(1);
	}
	write(minishell->fd, cwd, strlen(cwd));
	write(minishell->fd, "\n", 1);
	free(cwd);
	if (pipe)
	{
		ft_free_matriz(prompt);
		exit(0);
	}
	return (1);
}
