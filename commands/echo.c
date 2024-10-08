#include "../minishell.h"

int	count_line(char **argv)
{
	int	i;

	i = 0;
}


/*
tmp: Uma string vazia que será utilizada para construir a linha de comando final, após a expansão das variáveis de ambiente.
i, j, k: Variáveis inteiras usadas como índices para percorrer os argumentos e caracteres.
Itera sobre cada argumento passado para a função.
Itera sobre cada caractere do argumento.
Se encontrar um '$', busca pelo nome da variável de ambiente e substitui o nome da variável pelo seu valor.
se o seu valor for encontrado ele sera concatenado em tmp. se nao apenas reorna nul e volta a contar o proximo caracter.
Concatena os caracteres (ou valores das variáveis) à string tmp.
*/
int		command_echo(char **argv, char *cmd, char *bin)
{
	extern char **environ;
	char		*env_var_name;
	char		*env_var_value;
	char 		single_char[2];
	char 		*tmp;
	char 		*arg;
	pid_t 		pid;
	int			i;
	int			j;
	int			k;

	tmp = ft_strdup("");
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
					tmp = ft_strjoin(tmp, env_var_value);
				free(env_var_name);
				j = k;
			}
			else
			{
				single_char[0] = arg[j];
				single_char[1] = '\0';
				tmp = ft_strjoin(tmp, single_char);
				j++;
			}
		}
		tmp = ft_strjoin(tmp, " ");
	}
	pid = fork();
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
	free(tmp);
	return (0);
}
