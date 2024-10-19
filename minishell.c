#include "minishell.h"

void	handle_SIGINT(int signal)
{
	char *cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_putstr_fd(VERDE "\n┌──" RESET, 1);
		ft_putstr_fd(AZUL "(Minishell)" RESET, 1);
		ft_putstr_fd(VERDE "-[" RESET, 1);
		ft_putstr_fd(cwd, 1);
		ft_putstr_fd(VERDE "]\n", 1);
		free(cwd);
	}
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	main(int ac, char **av)
{
	t_minishell	minishell;
	int		status;
    char    *cwd;

	signal(SIGINT, handle_SIGINT);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		ft_putstr_fd(VERDE "\n┌──" RESET, 1);
		ft_putstr_fd(AZUL "(Minishell)" RESET, 1);
		ft_putstr_fd(VERDE "-[" RESET, 1);
		cwd = getcwd(NULL, 0);
        ft_putstr_fd(cwd, 1);
		ft_putstr_fd(VERDE "]", 1);
		minishell.readline = readline(VERDE "\n└─" RESET AZUL "# " RESET);
		if (!minishell.readline)
        {
            free(cwd);
            free(minishell.readline);
			exit (0);
        }
		if (minishell.readline)
			add_history(minishell.readline);
		if (ft_strncmp(minishell.readline, "exit", 4) == 0)
		{
			free(minishell.readline);
            free(cwd);
			exit(0);
		}
		else
			execute_command(&minishell);
		while (waitpid(-1, &status, 0) > 0)
			;
		free(minishell.readline);
        free(cwd);
	}
	return (0);
}