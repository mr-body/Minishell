/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 01:59:39 by waalexan          #+#    #+#             */
/*   Updated: 2024/11/10 18:40:32 by gkomba           ###   ########.fr       */
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

// static char	*get_input(t_mini *ms, const char *prompt)
// {
// 	char	*input;

// 	input = readline (prompt);
// 	if (input && input[0])
// 		add_history (input);
// 	else if (!input)
// 		exit_handler (ms, EXIT_MSG, 0);
// 	return (input);
// }

static void	get_readline(t_minishell *minishell)
{
	minishell->readline = readline(AMARELO "minishell" VERDE "# " RESET);
	if (!minishell->readline)
	{
		free(minishell->readline);
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	if (minishell->readline)
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

// static char	*get_input(t_mini *ms, const char *prompt)
// {
// 	char	*input;

// 	input = readline (prompt);
// 	if (input && input[0])
// 		add_history (input);
// 	else if (!input)
// 		exit_handler (ms, EXIT_MSG, 0);
// 	return (input);
// }

// static t_mini	ft_init(int argc, char *argv[], char **envp)
// {
// 	t_mini				ms;
// 	struct sigaction	sa;

// 	(void) argv;
// 	ft_bzero (&ms, sizeof (t_mini));
// 	if (argc > 1)
// 		exit_handler (&ms, "Usage: ./minishell", 1);
// 	ft_bzero (&sa, sizeof (sa));
// 	sa.sa_flags = SA_SIGINFO;
// 	sa.sa_sigaction = ft_sa_handler;
// 	sigaction (SIGINT, &sa, NULL);
// 	signal(SIGQUIT, SIG_IGN);
// 	ms.envp = ft_matdup (envp);
// 	if (!envp)
// 		exit_handler (&ms, "Can't allocate memory to environment variables", 1);
// 	ms.prompt = ft_strdup("minishell > ");
// 	if (!ms.prompt)
// 		exit_handler (&ms, "Can't allocate memory to prompt name", 1);
// 	return (ms);
// }

// ms.input = get_input (&ms, ms.prompt);