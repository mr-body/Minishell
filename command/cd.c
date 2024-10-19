#include "../minishell.h"

int	command_cd(char **prompt)
{
	if (prompt[1])
	{
		if (chdir(prompt[1]) != 0)
		{
			perror("cd error");
			return (1);
		}
	}
	return (0);
}