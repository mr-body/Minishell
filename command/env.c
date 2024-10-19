#include "../minishell.h"

int	command_env(char **prompt, char **environ)
{
	int	i;

	i = -1;
	while (environ[++i])
	{
		write(1, environ[i], ft_strlen(environ[i]));
		write(1, "\n", 1);
	}
	exit(0);
	return (0);
}