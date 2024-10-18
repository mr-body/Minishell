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

int	command_exit(char **prompt)
{
	exit(0);
}

int	command_echo(char **prompt, int pipe)
{
	int	i;

	i = 0;
	while (prompt[++i])
	{
		write(1, prompt[i], ft_strlen(prompt[i]));
		write(1, " ", 1);
	}
	write(1, "\n", 1);
	if (pipe)
	{
		ft_free_matriz(prompt);
		exit(0);
	}
	return (0);
}

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

int	command_pwd(char **prompt, int pipe)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("getcwd error");
		exit(1);
	}
	write(STDOUT_FILENO, cwd, strlen(cwd));
	write(STDOUT_FILENO, "\n", 1);
	free(cwd);
	if (pipe)
	{
		ft_free_matriz(prompt);
		exit(0);
	}
	return 1;
}

int	command_export(char **prompt)
{
	exit(0);
}

int	command_unset(char **prompt)
{
	exit(0);
}
