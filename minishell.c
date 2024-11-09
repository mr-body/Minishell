/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 01:59:39 by waalexan          #+#    #+#             */
/*   Updated: 2024/11/09 13:59:12 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	g_redsplay;

void	handle_sigint(int signal)
{
	(void)signal;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	if (g_redsplay)
		rl_redisplay();
}

void	get_readline(t_minishell *minishell)
{
	minishell->readline = readline(AMARELO "minishell" VERDE "# " RESET);
	g_redsplay = 0;
	if (!minishell->readline)
	{
		free(minishell->readline);
		exit(0);
	}
	if (minishell->readline)
	{
		add_history(minishell->readline);
	}
	if (ft_strncmp(minishell->readline, "exit",
			ft_strlen(minishell->readline)) == 0)
	{
		free(minishell->readline);
		exit(0);
	}
	else
		execute_command(minishell);
}

int	main(int ac, char **av, char **env)
{
	t_minishell	minishell;

	g_redsplay = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	ft_memset(&minishell, 0, sizeof(t_minishell));
	increment_shell_level(&minishell);
	while (1)
	{
		g_redsplay = 1;
		get_readline(&minishell);
		while (waitpid(-1, &minishell.status, 0) > 0)
			;
		free(minishell.readline);
	}
	return (0);
}
