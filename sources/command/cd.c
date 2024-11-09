/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:20:47 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/09 16:13:33 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	command_cd(char **prompt, t_minishell *minishell)
{
	char	*wdir;

	if (prompt[1])
	{
		wdir = getenv("PWD");
		change_old_pwd(wdir, minishell);
		if (chdir(prompt[1]) != 0)
		{
			perror("cd error");
			return (ft_ctrl_c(1), 1);
		}
		wdir = getcwd(NULL, 0);
		change_pwd(wdir, minishell);
		wdir = free_ptr(wdir);
	}
	return (ft_ctrl_c(0), 0);
}
