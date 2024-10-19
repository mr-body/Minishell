/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:20:47 by gkomba            #+#    #+#             */
/*   Updated: 2024/10/19 16:22:00 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	command_cd(char **prompt)
{
	if (prompt[1])
	{
		if (chdir(prompt[1]) != 0)
		{
			perror("cd error");
			return (1);
		}
	}
	return (0);
}
