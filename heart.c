#include "minishell.h"

char *ft_strcat(char *s1, char *s2)
{
    int i;
    int j;
    char *new;

    i = 0;
    j = 0;
    new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    while (s1[i])
    {
        new[i] = s1[i];
        i++;
    }  
    new[i++] = '/';
    while(s2[j])
    {
        new[i] = s2[j];
        i++;
        j++;
    }
    new[i] = '\0';
    return new;
    
}

char    **get_path(char const *str)
{
    int     len_cd;
    int     len_str;
    char    **mat;
    char    *cd;
    char    *path;
    char    *path_trimmed;

    len_str = ft_strlen(str);
    len_cd = ft_strlen("cd");
    mat = malloc(2 * sizeof(char *));
    if (!mat)
        return NULL;
    mat[0] = ft_substr(str, 0, len_cd);
    mat[1] = ft_substr(str, len_cd + 1, (len_str - len_cd)); 
    return mat;
}


void execute(char *cmd, t_minishell *minishell)
{
    // char **argv = ft_split(cmd, ' ');
    char    **argv = get_path(cmd);
    char **routes = ft_split(getenv("PATH"), ':');
    char    *bin;
    extern char **environ;
    int i = 0;

    if (access(argv[0], X_OK) == 0)
    {
        bin = strdup(argv[0]);
        if (!bin)
        {
            perror("error");
            free(argv);
            return;
        }
    }
    else
    {
        while(routes[i])
        {
            if (access(ft_strcat(routes[i], argv[0]), X_OK) == 0)
            {
                bin = ft_strcat(routes[i], argv[0]);
                break; 
            }
            i++;
        }
    }
    if(!ft_strncmp(argv[0], "cd", sizeof(argv[0])))
    {
        if(argv[1])
        {
            if(chdir(argv[1]) != 0)
                perror("error");
        }
        else
        {
            if(chdir(getenv("HOME")) != 0)
                perror("erro&&r");
        }
        minishell->dir = getcwd(NULL, 0);
        return;
    }
    else if(!ft_strncmp(argv[0], "exit", sizeof(argv[0])))
        exit(0);

    pid_t pid = fork();
    if(pid == 0)
    {
        if(execve(bin, argv, environ) == -1)
        {
            perror("error");
            exit(1);
        }
    }
    else if(pid > 0)
        waitpid(pid, NULL, 0);
    else
        perror("error");
    free(argv);
}

void command(t_minishell *minishell)
{
    
    char *command;

    while(1)
    {
        ft_putstr_fd(VERDE "\n┌──" RESET, 1);
        ft_putstr_fd(AZUL "(Minishell)" RESET, 1); 
        ft_putstr_fd(VERDE "-[" RESET, 1);
        ft_putstr_fd(minishell->dir, 1);
        ft_putstr_fd(VERDE "]", 1);
        command = readline(VERDE  "\n└─" RESET AZUL "# " RESET);
        if(!command)
            break;

        if(command)
            add_history(command);

        execute(command, minishell);

        rl_on_new_line();
        free(command);
    }
}
