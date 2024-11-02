#include "minishell.h"

static int	g_redsplay = 0;

void	handle_SIGINT(int signal)
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
	minishell->readline = readline("Minishell > ");
	if (!minishell->readline)
	{
		free(minishell->readline);
		exit(0);
	}
	if (minishell->readline)
	{
		// put
		add_history(minishell->readline);
	}
	if (ft_strncmp(minishell->readline, "exit", 4) == 0)
	{
		free(minishell->readline);
		exit(0);
	}
	else
		execute_command(minishell);
}

int	main(int ac, char **av)
{
	t_minishell	minishell;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_SIGINT);
	ft_memset(&minishell, 0, sizeof(t_minishell));
	increment_shell_level(&minishell);
	while (1)
	{
		g_redsplay = 1;
		get_readline(&minishell);
		g_redsplay = 0;
		while (waitpid(-1, &minishell.status, 0) > 0)
			;
		free(minishell.readline);
	}
	return (0);
}
