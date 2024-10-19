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
void set_to_env(const char *name, const char *value, char **environ) {
    int i = 0;
    char *new_var;
    size_t name_len = strlen(name);
    
    // Allocate memory for the new environment variable
    new_var = malloc(name_len + strlen(value) + 2); // +2 for '=' and '\0'
    if (!new_var) {
        perror("Failed to allocate memory for new environment variable");
        return;
    }

    // Create the new variable string
    sprintf(new_var, "%s=%s", name, value);

    // Look for the variable in the environment
    while (environ[i]) {
        if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=') {
            // Variable found, replace it
            free(environ[i]);
            environ[i] = new_var;
            return;
        }
        i++;
    }

    // Variable not found, add it to the end
    environ[i] = new_var;
    environ[i + 1] = NULL; // Ensure the last element is NULL
}

char **args(char *prompt)
{
    char **raw_data;
    char **net_data;
    char **data;

    raw_data = ft_split(prompt , '=');
    net_data = ft_adjust_data(raw_data);
    if (!net_data)
	{
		write(1, "minishell: syntax error: quote\n", 31);
        	ft_free_matriz(raw_data);
		exit(1);
	}
    data = ft_extended(net_data);
    ft_free_matriz(raw_data);
    ft_free_matriz(net_data);
    return(data);
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
		while(prompt[++i])
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