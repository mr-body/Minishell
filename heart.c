#include "minishell.h"

int sheel(char **prompt, int pipe)
{
    extern char **environ;
    char **routes;
    char *command = NULL;
    int i = -1;
    int exit_status;

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
                break;
            free(command);
            command = NULL;
        }
    }
    if (ft_strncmp(prompt[0], "exit", 4) == 0)
    {
        ft_free_matriz(routes);
        ft_free_matriz(prompt);
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
    else
    {
        if (command == NULL)
        {
            ft_free_matriz(routes);
            return (-1);
        }
        execve(command, prompt, environ);
        free(command);
        ft_free_matriz(routes);
        return (-1);
    }
    ft_free_matriz(routes);
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
	return (0);
}

void	execute_command(t_minishell	*minishell)
{
	int num_commands;
	int exit_status;
	int i;
	int j;

	i = -1;
	if (ft_strchr(minishell->readline, '|'))
	{
		minishell->raw_args = ft_split(minishell->readline, '|');
		num_commands = ft_matriz_len(minishell->raw_args);
		minishell->pipe_fds = (int *)malloc(sizeof(int) * (2 * num_commands - 1));
		while (++i < num_commands - 1)
			if (pipe(minishell->pipe_fds + i * 2) < 0)
				perror("pipe error");
		i = -1;
		while (++i < num_commands)
		{
			minishell->args = net_args(minishell->raw_args[i]);
			pid_t pid = fork();
			if (pid == 0)
			{
				if (i < num_commands - 1)
					dup2(minishell->pipe_fds[i * 2 + 1], STDOUT_FILENO);
				if (i > 0)
					dup2(minishell->pipe_fds[(i - 1) * 2], STDIN_FILENO);

				j = -1;
				while (++j < 2 * (num_commands - 1))
					close(minishell->pipe_fds[j]);
				if (sheel(minishell->args, 1) == -1)
					perror("error: ");
			}
			else if (pid < 0)
				perror("fork error: ");
			ft_free_matriz(minishell->args);
		}
		i = 0;
		while (i < 2 * (num_commands - 1))
		{
			close(minishell->pipe_fds[i]);
			i++;
		}
		minishell->pipe_fds = (int *)free_ptr((char *)minishell->pipe_fds);
		ft_free_matriz(minishell->raw_args);
	}
	else
	{
		minishell->args = net_args(minishell->readline);
		if (!is_builtin(minishell->args[0]))
		{
			pid_t pid = fork();
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
			{
				waitpid(pid, &exit_status, 0);
				if (WIFEXITED(exit_status) && WEXITSTATUS(exit_status) != 0)
					printf("Child process exited with status: %d\n",
						WEXITSTATUS(exit_status));
			}
		}
		else
		{
			if (sheel(minishell->args, 0) == -1)
				perror("error: ");
		}
		ft_free_matriz(minishell->args);
	}
}