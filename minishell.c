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
	char	*prompt;
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
		prompt = readline(VERDE "\n└─" RESET AZUL "# " RESET);
		if (!prompt)
        {
            free(cwd);
            free(prompt);
			exit (0);
        }
		if (*prompt)
			add_history(prompt);
		if (ft_strncmp(prompt, "exit", 4) == 0)
		{
			free(prompt);
            free(cwd);
			exit(0);
		}
		else
			execute_command(prompt);
		while (waitpid(-1, &status, 0) > 0)
			;
		free(prompt);
        free(cwd);
	}
	return (0);
}
