#include "minishell.h"

int	sheel(char **prompt, int pipe)
{
	extern char	**environ;
	char		**routes;
	char		*command;
	int			i;
	int			exit_status;

	command = NULL;
	i = -1;
	routes = ft_split(getenv("PATH"), ':');
	if (access(prompt[0], X_OK) == 0)
	{
		command = prompt[0];
	}
	else
	{
		while (routes[++i])
		{
			command = ft_strcat(routes[i], prompt[0], '/');
			if (access(command, X_OK) == 0)
				break ;
			command = free_ptr(command);
		}
	}
	if (ft_strncmp(prompt[0], "exit", 4) == 0)
	{
		routes = ft_free_matriz(routes);
		prompt = ft_free_matriz(prompt);
		exit(0);
	}
	else if (ft_strncmp(prompt[0], "env", 3) == 0)
		exit_status = command_env(prompt, environ);
	else if (ft_strncmp(prompt[0], "cd", 2) == 0)
		exit_status = command_cd(prompt);
	else if (ft_strncmp(prompt[0], "echo", 4) == 0)
		exit_status = command_echo(prompt, pipe);
	else if (ft_strncmp(prompt[0], "pwd", 3) == 0)
		exit_status = command_pwd(prompt, pipe);
	else if (ft_strncmp(prompt[0], "export", 6) == 0)
		exit_status = command_export(prompt, pipe);
	else
	{
		if (command == NULL)
		{
			routes = ft_free_matriz(routes);
			return (-1);
		}
		execve(command, prompt, environ);
		command = free_ptr(command);
		routes = ft_free_matriz(routes);
		return (-1);
	}
	routes = ft_free_matriz(routes);
	return (exit_status);
}

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "exit", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 6) == 0)
		return (1);
	return (0);
}

void	exec_command(t_minishell *minishell)
{
	int		exit_status;
	pid_t	pid;

	minishell->args = net_args(minishell->readline);
	if (!is_builtin(minishell->args[0]))
	{
		pid = fork();
		if (pid < 0)
			perror("fork error: ");
		else if (pid == 0)
		{
			if (sheel(minishell->args, 0) == -1)
			{
				perror("exec error: ");
				exit(EXIT_FAILURE);
			}
		}
		else
			waitpid(pid, &minishell->exit_status, 0);
	}
	else
	{
		if (sheel(minishell->args, 0) == -1)
			perror("error: ");
	}
	ft_free_matriz(minishell->args);
}

void	exec_command_pipe(t_minishell *minishell)
{
	int		num_commands;
	int		i;
	pid_t	pid;

	minishell->raw_args = ft_split(minishell->readline, '|');
	num_commands = ft_matriz_len(minishell->raw_args);
	minishell->pipe_fds = (int *)malloc(sizeof(int) * (2 * num_commands - 1));
	open_fds(minishell, num_commands);
	i = -1;
	while (++i < num_commands)
	{
		minishell->args = net_args(minishell->raw_args[i]);
		pid = fork();
		if (pid == 0)
		{
			if (i < num_commands - 1)
				dup2(minishell->pipe_fds[i * 2 + 1], STDOUT_FILENO);
			if (i > 0)
				dup2(minishell->pipe_fds[(i - 1) * 2], STDIN_FILENO);
			close_fds(minishell, num_commands);
			if (sheel(minishell->args, 1) == -1)
				perror("error: ");
		}
		else if (pid < 0)
			perror("fork error: ");
		ft_free_matriz(minishell->args);
	}
	ft_exit_process(minishell, num_commands);
}

void	execute_command(t_minishell *minishell)
{
	if (strchr(minishell->readline, '|'))
		exec_command_pipe(minishell);
	else
		exec_command(minishell);
}