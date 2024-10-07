#include "../minishell.h"

int	count_line(char **argv)
{
	int	i;

	i = 0;
}

int	command_echo(char **argv, char *cmd, char *bin)
{
	extern char **environ;
	char *tmp = ft_strdup("");
	int i = 0;
    int start = 0;
    int end = -1;

	while (argv[++i])
	{
        if (ft_strchr(argv[i], '$'))
        {
            while(argv[i][++end] != '$')
                ;
            tmp = ft_strjoin(tmp, ft_substr(argv[i], start, end));
            if (ft_strchr(argv[i], '$'))
            {
                if (getenv((ft_strchr(argv[i], '$') + 1)) != NULL)
                    tmp = ft_strjoin(tmp, getenv((ft_strchr(argv[i], '$') + 1)));
            }
        }
        else{
            tmp = ft_strjoin(tmp, argv[i]);
        }
        tmp = ft_strjoin(tmp, " ");
	}

    //teste$HOME$PATH
    //0123456789

	pid_t pid = fork();
	if (pid == 0)
	{
        char *args[] = {bin, tmp, NULL};
		if (execve(bin, args, environ) == -1)
		{
			perror("error");
			exit(1);
		}
	}
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);
	}
	else
	{
		perror("error");
		exit(1);
	}

	return (0);
}