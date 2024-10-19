#include "minishell.h"

void	open_fds(t_minishell *minishell, int nbr_cmds)
{
	int	i;

	i = 0;
	while (i < nbr_cmds - 1)
	{
		if (pipe(minishell->pipe_fds + i * 2) < 0)
			perror("pipe error");
		i++;
	}
}

void	close_fds(t_minishell *minishell, int nbr_cmds)
{
	int	i;

	i = 0;
	while (i < 2 * (nbr_cmds - 1))
	{
		close(minishell->pipe_fds[i]);
		i++;
	}
}

void	ft_exit_process(t_minishell *minishell, int nbr_cmds)
{
    close_fds(minishell, nbr_cmds);
	minishell->pipe_fds = (int *)free_ptr((char *)minishell->pipe_fds);
	minishell->raw_args = ft_free_matriz(minishell->raw_args);
}