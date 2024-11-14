/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:20:47 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/12 16:55:32 by gkomba           ###   ########.fr       */
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
		ft_delete_chr_on_str(prompt[1], '\'');
		ft_delete_chr_on_str(prompt[1], '\"');
		printf("prompt[1]: %s\n", prompt[1]);
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