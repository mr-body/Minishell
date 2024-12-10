/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:41:08 by gkomba            #+#    #+#             */
/*   Updated: 2024/12/07 14:43:07 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_if_str_is_pipe(t_minishell *minishell)
{
	if (check_if_str_is_pipe(minishell->check_data) == 1)
	{
		ft_free_matriz(minishell->check_data);
		minishell->exit_status = exec_command_pipe(minishell);
	}
	else
	{
		ft_free_matriz(minishell->check_data);
		minishell->args = net_args(minishell->command);
		if (ft_strlen(minishell->args->args[0]) == 0
			|| ft_is_only(minishell->args->args[0], ' '))
			return (0);
		minishell->exit_status = exec_command(minishell);
	}
	return (1);
}

int	is_not_new(char *value)
{
	extern char	**environ;
	int			i;

	if (!environ)
		return (0);
	i = 0;
	while (environ[i])
	{
		if (!ft_strncmp2(environ[i], value, ft_strlen(value)))
			return (1);
		i++;
	}
	return (0);
}
