/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 01:59:11 by waalexan          #+#    #+#             */
/*   Updated: 2024/11/15 12:12:36 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handing_c(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n", 1);
}

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->count)
	{
		free(data->args[i]);
	}
	free(data->args);
	free(data->types);
	free(data);
}

int	is_new_prompt(t_minishell *minishell)
{
	if (ft_strcmp(minishell->readline, "gkomba") == 0)
	{
		minishell->gkomba = 1;
		minishell->waalexan = 0;
		minishell->ms = 0;
		return (ft_prompt_sms('g'), 0);
	}
	else if (ft_strcmp(minishell->readline, "waalexan") == 0)
	{
		minishell->waalexan = 1;
		minishell->gkomba = 0;
		minishell->ms = 0;
		return (ft_prompt_sms('w'), 0);
	}
	else if (ft_strcmp(minishell->readline, "ms") == 0
		&& (minishell->waalexan == 1 || minishell->gkomba == 1))
	{
		minishell->ms = 1;
		minishell->waalexan = 0;
		minishell->gkomba = 0;
		return (ft_prompt_sms('m'), 0);
	}
	return (1);
}
