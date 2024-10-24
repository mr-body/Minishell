/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:20:18 by gkomba            #+#    #+#             */
/*   Updated: 2024/10/19 16:21:49 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	command_pwd(char **prompt, int pipe)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("getcwd error");
		exit(1);
	}
	write(STDOUT_FILENO, cwd, strlen(cwd));
	write(STDOUT_FILENO, "\n", 1);
	free(cwd);
	if (pipe)
	{
		ft_free_matriz(prompt);
		exit(0);
	}
	return (1);
}
