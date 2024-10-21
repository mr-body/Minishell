#include "../minishell.h"

char	**sort_env(char **environ)
{
	int		argc;
	char	*temp;
	int		i;
	int		j;

	argc = ft_matriz_len(environ);
	i = 0;
	while (i < argc - 1)
	{
		j = 0;
		while (j < argc - 1 - i)
		{
			if (strcmp(environ[j], environ[j + 1]) > 0)
			{
				temp = environ[j];
				environ[j] = environ[j + 1];
				environ[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	return (environ);
}
void	set_to_env(const char *name, const char *value, char **environ)
{
	int		i;
	char	*new_var;
	size_t	name_len;

	i = 0;
	name_len = strlen(name);
    new_var = NULL;
	new_var = ft_strjoin(name, "=");
	new_var = ft_strjoin(new_var, value);
	while (environ[i])
	{
		if (strncmp(environ[i], name, name_len) == 0
			&& environ[i][name_len] == '=')
		{
			free(environ[i]);
			environ[i] = new_var;
			return ;
		}
		i++;
	}
	environ[i] = new_var;
	environ[i + 1] = NULL;
}

int	command_export(char **prompt, int pipe)
{
	extern char **environ;
	char **sorted_env = sort_env(environ);
	char **pramentres;
	int i = 0;

	if (!prompt[1])
	{
		while (sorted_env[i])
		{
			char *output = ft_strjoin("declare -x ", sorted_env[i]);
			ft_putstr_fd(output, 1);
			free(output);
			write(1, "\n", 1);
			i++;
		}
	}
	else
	{
		i = 0;
		while (prompt[++i])
		{
			pramentres = ft_split(prompt[i], '=');
			set_to_env(pramentres[0], pramentres[1], environ);
		}
	}
	if (pipe)
	{
		ft_free_matriz(prompt);
		exit(0);
	}
	return (0);
}