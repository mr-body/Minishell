
#include "minishell.h"

void	execute(char *cmd, t_minishell *minishell)
{
	char		**argv;
	char		**routes;
	char		*bin;
	extern char	**environ;
	int			i;
	pid_t		pid;

	argv = ft_split(cmd, ' ');
	routes = ft_split(getenv("PATH"), ':');
	i = 0;
	// 1- passo : verifica se o executavel este neste directorio (./exempli)
	if (access(argv[0], X_OK) == 0)
	{
		bin = ft_strdup(argv[0]);
		if (!bin)
		{
			perror("error");
			free(argv);
			return ;
		}
	}
	// 2- passo : busca o exceutavel nas pastas das variaves e ambiente $PATH
	else
	{
		while (routes[i])
		{
			if (access(ft_strcat(routes[i], argv[0], '/'), X_OK) == 0)
			{
				bin = ft_strcat(routes[i], argv[0], '/');
				break ;
			}
			i++;
		}
	}
	// implementacao do comando [cd]
	if (!ft_strncmp(argv[0], "cd", ft_strlen(argv[0])))
	{
		if (!command_cd(argv, cmd, minishell))
			return ;
		else
			return (perror("error"));
	}
	// implementacao do comando [echo]
	else if (!ft_strncmp(argv[0], "echo", ft_strlen(argv[0])))
	{
		if (!command_echo(argv, cmd, bin))
			return ;
		else
			return (perror("error"));
	}
	// implementacao do comando [exit]
	else if (!ft_strncmp(argv[0], "exit", sizeof(argv[0])))
		exit(0);
	// inicar processo filho para execuar um commando em segundo plano
	pid = fork();
	if (pid == 0)
	{
		if (execve(bin, argv, environ) == -1)
		{
			perror("error");
			exit(1);
		}
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
		perror("error");
	free(argv);
}

void	command(t_minishell *minishell)
{
	char	*command;

	while (1)
	{
		ft_putstr_fd(VERDE "\n┌──" RESET, 1);
		ft_putstr_fd(AZUL "(Minishell)" RESET, 1);
		ft_putstr_fd(VERDE "-[" RESET, 1);
		ft_putstr_fd(minishell->dir, 1);
		ft_putstr_fd(VERDE "]", 1);
		command = readline(VERDE "\n└─" RESET AZUL "# " RESET);
		// Ctrl + D
		if (!command)
			break ;
		// adiciona o camando nos historico de comandos
		if (command)
			add_history(command);
		// executa os comandos
		execute(command, minishell);
		// preparar para rendereizar uma nova linha
		rl_on_new_line();
		free(command);
	}
}
