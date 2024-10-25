/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:20:47 by gkomba            #+#    #+#             */
/*   Updated: 2024/10/22 11:59:09 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



int	command_cd(char **prompt, char **env)
{
	char	**pwds;

	pwds = (char **)malloc(sizeof(char *) * 3);
	if (!pwds)
	{
		perror("cd error");
		return (1);
	}
	pwds[0] = "OLD_PWD=";
	pwds[1] = prompt[1];
	pwds[2] = NULL;
	command_export(pwds, env, 0);
	if (prompt[1])
	{
		if (chdir(prompt[1]) != 0)
		{
			perror("cd error");
			return (1);
		}
	}
	pwds = ft_free_matriz(pwds);
	return (0);
}
