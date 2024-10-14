#include "minishell.h"

int sheel(char **prompt)
{
    extern char **environ;
    char **routes;
    char *command;
    int i;
    
    i = -1;
    routes = ft_split(getenv("PATH"), ':');
    if(access(prompt[0], X_OK) == 0)
        command = prompt[0];
    else
    {
        while(routes[++i])
        {
            if(access(ft_strcat(routes[i], prompt[0], '/'), X_OK) == 0)
            {
                command = ft_strcat(routes[i], prompt[0], '/');
                break;
            }
        }
    }
    if(ft_strncmp(prompt[0], "exit", 4) == 0)
        command_exit(prompt);
    else if(ft_strncmp(prompt[0], "env", 3) == 0)
        command_env(prompt, environ);
    else if(ft_strncmp(prompt[0], "cd", 2) == 0)
        command_cd(prompt);
    else if(ft_strncmp(prompt[0], "echo", 4) == 0)
        command_echo(prompt);
    else if(ft_strncmp(prompt[0], "pwd", 3) == 0)
        command_pwd(prompt);
    else
    {
        execve(command, prompt, environ);
        return (-1);
    }
    return (0);
}

void execute_command(char *prompt)
{
    char **raw_args;
    char **args;
    int num_commands;
    int *pipe_fds;
    int i;
    int j;

    i = -1;
    raw_args = ft_split(prompt, '|');
    num_commands = ft_matriz_len(raw_args);
    pipe_fds = (int *)malloc(sizeof(int) * 2 * (num_commands - 1));
    while(++i < num_commands - 1)
        if(pipe(pipe_fds + i * 2) < 0)
            perror("pipe error");
    i = -1;
    while(++i < num_commands)
    {
        args = net_args(raw_args[i]);
        pid_t pid = fork();
        if(pid == 0)
        {
            if(i < num_commands - 1)
                dup2(pipe_fds[i * 2 + 1], STDOUT_FILENO);
            if(i > 0)
                dup2(pipe_fds[(i - 1) * 2], STDIN_FILENO);
            
            j = -1;
            while(++j < 2 * (num_commands - 1))
                close(pipe_fds[j]);
            if(sheel(args) == -1)
                perror("error: ");
        }
        else if(pid < 0)
            perror("fork error");
    }
    i = -1;
    while(++i < 2 * (num_commands - 1))
        close(pipe_fds[i]);
    free(pipe_fds);
}