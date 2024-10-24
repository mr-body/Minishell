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
	char	*old_var;
	size_t	name_len;

	i = 0;
	name_len = ft_strlen(name);
    new_var = NULL;
	new_var = ft_strjoin(name, "=");
	old_var = new_var;
	new_var = ft_strjoin(new_var, value);
	free(old_var);
	while (environ[i])
	{
		if (ft_strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
		{
			free(environ[i]);
			environ[i] = new_var;
			return ;
		}
		i++;
	}
	environ[i] = new_var;
	if (new_var)
		free(new_var);
	//environ[i + 1] = NULL;
}

int	command_export(char **prompt, int pipe)
{
	extern char **environ;
	char **sorted_env;
	char **declare;
	char *tmp;
	char	*old_tmp;
	char *output;
	char **pramentres;
	int i;
	sorted_env = sort_env(environ);
	if (!prompt[1])
	{
		i = 0;
		while (sorted_env[i])
		{
			declare = ft_split(sorted_env[i], '=');
			tmp = ft_strjoin(declare[0], "=\"");
			old_tmp = tmp;
			tmp = ft_strjoin(tmp, declare[1]);
			free(old_tmp);
			old_tmp = tmp;
			tmp = ft_strjoin(tmp, "\"");
			free(old_tmp);
			output = ft_strjoin("declare -x ", tmp);
			ft_putendl_fd(output, 1);
			free(output);
			ft_free_matriz(declare);
			free(tmp);
			i++;
		}
	}
	else
	{
		i = 0;
		while (prompt[++i])
		{
			pramentres = ft_split(prompt[i], '=');
			tmp = ft_strtrim(pramentres[1],  "\"" );
			set_to_env(pramentres[0], tmp, environ);
			ft_free_matriz(pramentres);
			free(tmp);
		}
	}
	if (pipe)
	{
		ft_free_matriz(prompt);
		exit(0);
	}
	return (0);
}