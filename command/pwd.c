/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:20:18 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/09 11:07:52 by waalexan         ###   ########.fr       */
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
		minishell->process_out = 0;
		exit(0);
	}
	return (minishell->process_out = 0, 0);
}
