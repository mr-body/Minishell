#include "../minishell.h"

int	count_line(char **argv)
{
	int	i;

	i = 0;
}

int	command_echo(char **argv, char *cmd, char *bin)
{
	extern char **environ;
	char 	*tmp = ft_strdup("");
	int 	i;
	char *arg;
	char *env_var_name;
	char *env_var_value;
	int j;
	int	k;

	i = 0;
	while (argv[++i])
	{
		arg = argv[i];
		j = 0;
		while (arg[j])
		{
			if (arg[j] == '$')
			{
				j++;
				k = j;
				while (arg[k] && (ft_isalnum(arg[k]) || arg[k] == '_')) 
					k++;
				printf("j ->> %d || k ->>> %d\n", j, k);
				env_var_name = ft_substr(arg, j, k - j);
				env_var_value = getenv(env_var_name);
				
				if (env_var_value)
				{
					tmp = ft_strjoin(tmp, env_var_value);
				}
				free(env_var_name);
				j = k;
			}
			else
			{
				char single_char[2] = {arg[j], '\0'};
				tmp = ft_strjoin(tmp, single_char);
				j++;
			}
		}
		tmp = ft_strjoin(tmp, " ");
	}
	pid_t pid = fork();
	if (pid == 0)
	{
		char *args[] = {bin, tmp, "-c"};
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
	free(tmp);
	return (0);
}
