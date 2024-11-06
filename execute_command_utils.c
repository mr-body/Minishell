/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:03:07 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/06 18:06:39 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	extract_command(t_minishell *minishell, int *redir, int *retrn)
{
	*retrn = 0;
	minishell->args = net_args(minishell->command);
	*redir = is_redir(minishell->command);
	minishell->redirect_command = minishell->command;
	if (!minishell->args)
	{
		free_data(minishell->args);
		*retrn = 1;
		return (1);
	}
	if (!minishell->args->args[0])
	{
		*retrn = 0;
		return (1);
	}
	return (0);
}

void	last_redir(t_minishell *minishell)
{
	int	len;

	len = ft_matriz_len(minishell->raw_args->args);
	if (ft_strchr(minishell->raw_args->args[len - 1], '>')
		|| ft_strchr(minishell->raw_args->args[len - 1], '>>'))
		minishell->last = 1;
	else
		minishell->last = 0;
}
