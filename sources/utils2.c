/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:41:08 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/12 17:13:50 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redir_is_not_followed_by_pipe(char **matriz)
{
	int	i;

	i = 0;
	while (matriz[i])
	{
		if (ft_strncmp(matriz[i], "<|", 2) == 0)
		{
			redir_syntax_error("PANCAKE");
			return (1);
		}
		else if (ft_strncmp(matriz[i], "<<|", 3) == 0)
		{
			redir_syntax_error("PANCAKE");
			return (1);
		}
		i++;
	}
	return (0);
}
