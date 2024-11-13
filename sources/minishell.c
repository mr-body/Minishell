/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 01:59:39 by waalexan          #+#    #+#             */
/*   Updated: 2024/11/13 18:49:07 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_ctrl_c(int value)
{
	static int	status = 0;

	if (value != -1)
		status = value;
	return (status);
}

void	handle_sigint(int signal)
{
	(void)signal;
	ft_ctrl_c(130);
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	if (ft_ctrl_c(-1))
		rl_redisplay();
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
		minishell->readline = readline(AMARELO "minishell" VERDE "# " RESET);
		minishell->waalexan = 0;
		minishell->gkomba = 0;
		return (0);
	}
	return (1);
}

static void	get_readline(t_minishell *minishell)
{
	ft_prompt(minishell);
	if (!minishell->readline)
	{
		free(minishell->readline);
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	if (is_new_prompt(minishell) == 0)
		return ;
	else if (minishell->readline && !ft_is_only(minishell->readline, '\n'))
		add_history(minishell->readline);
	
	execute_command(minishell);
}

int	main(int argc, char **argv)
{
	t_minishell	minishell;

	if (argc != 1)
	{
		ft_putstr_fd("Error: No arguments needed\n", 2);
		exit(1);
	}
	(void)argv;
	ft_ctrl_c(1);
	ft_memset(&minishell, 0, sizeof(t_minishell));
	increment_shell_level(&minishell);
	minishell.ms = 1;
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_sigint);
		get_readline(&minishell);
		while (waitpid(-1, &minishell.status, 0) > 0)
			;
		free(minishell.readline);
	}
	return (0);
}
