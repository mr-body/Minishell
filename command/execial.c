#include "../minishell.h"

int command_cd(char **prompt)
{
    if(prompt[1])
        chdir(ft_strtrim(prompt[1], "\'"));
    else
        write(1, "\n", 1);
    return (0);
}

int command_exit(char **prompt)
{
    exit(0);
    return (0);
}

int command_echo(char **prompt)
{
    int i;
    i = 0;
    while(prompt[++i])
    {
        write(1, prompt[i], ft_strlen(prompt[i]));
        write(1, " ", 1);
    }
    write(1, "\n", 1);
    exit(0);
    return (0);
}

int command_env(char **prompt, char **environ)
{
    int i;

    i = -1;
    while(environ[++i])
        write(1, environ[i], ft_strlen(environ[i]));
    write(1, "\n", 1);
    exit(0);
    return (0);
}

int command_pwd(char **prompt)
{
    write(STDOUT_FILENO, getcwd(NULL, 0), ft_strlen(getcwd(NULL, 0)));
    write(STDOUT_FILENO, "\n", 1);
    exit(0);
    return (0);
}

int command_export(char **prompt)
{
    return (0);
}

int command_unset(char **prompt)
{
    return (0);
}