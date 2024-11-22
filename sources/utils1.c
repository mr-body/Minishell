/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 01:59:11 by waalexan          #+#    #+#             */
/*   Updated: 2024/11/22 15:55:29 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*return_cmd_path(char *cmd_path, char **routes)
{
	if (cmd_path == NULL)
		return (ft_free_matriz(routes), NULL);
	routes = ft_free_matriz(routes);
	return (cmd_path);
}

void	handing_c(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n", 1);
}

void	free_data(t_data *data)
{
	int	i;

	if (!data)
		return ;
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

int	ft_prompt(t_minishell *minishell)
{
	if (minishell->gkomba)
	{
		minishell->readline = readline(AMARELO "gkomba" VERDE "🧐> " RESET);
		minishell->waalexan = 0;
		minishell->ms = 0;
		return (1);
	}
	else if (minishell->waalexan)
	{
		minishell->readline = readline(AMARELO "Waalexan" VERDE "😎> " RESET);
		minishell->gkomba = 0;
		minishell->ms = 0;
		return (1);
	}
	else if (minishell->ms)
	{
		minishell->readline = readline("minishell# ");
		minishell->waalexan = 0;
		minishell->gkomba = 0;
		return (0);
	}
	return (1);
}
