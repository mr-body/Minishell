/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:59:09 by gkomba            #+#    #+#             */
/*   Updated: 2024/12/06 12:44:29 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_prompt_sms(char c)
{
	if (c == 'g')
		ft_putendl_fd(AZUL "gkomba >> Welcome Human 🪐" RESET, 1);
	else if (c == 'w')
		ft_putendl_fd(VERDE "waalexan >> Now. Waalexan is on control 🌍" RESET,
			1);
	else if (c == 'm')
		ft_putendl_fd(AMARELO "minishell >> Welcome to minishell 🌌" RESET, 1);
}

void	get_extra_prompt(t_minishell *minishell)
{
	char	*herepipe;

	while (ft_check_last_pipe(minishell->readline) == 1)
	{
		herepipe = readline("> ");
		if (!herepipe)
		{
			free(minishell->readline);
			ft_putendl_fd("syntax error: unexpected end of file", 1);
			ft_putendl_fd("exit", 1);
			exit(2);
		}
		minishell->temp = minishell->readline;
		minishell->readline = ft_strjoin(minishell->readline, herepipe);
		if (minishell->readline && !ft_is_only(minishell->readline, '\n'))
			add_history(minishell->readline);
		free(minishell->temp);
		free(herepipe);
	}
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
