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

void set_to_env(const char *name, const char *value, char **environ)
{
    int i;
    char *new_var;
    size_t name_len;

    name_len = ft_strlen(name);
    new_var = ft_strjoin(name, "=");
    char *old_var = new_var;  // Preserve original pointer for free

    new_var = ft_strjoin(new_var, value);
    free(old_var);  // Free the initial concatenation

    i = 0;
    while (environ[i])
    {
        if (ft_strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
        {
            free(environ[i]);  // Free the old variable
            environ[i] = new_var;  // Assign the new variable
            return;
        }
        i++;
    }

    environ[i] = new_var;  // Set the new variable in the environment
    environ[i + 1] = NULL; // Ensure the next pointer is NULL
}

int command_export(char **prompt, char **env, int pipe)
{
    char **sorted_env;
    char **declare;
    char *tmp;
    char *old_tmp;
    char *output;
    char **parameters;
    int i;

    sorted_env = sort_env(env);
    if (!sorted_env)
        return 1; // Error handling for sort_env failure

    if (!prompt[1])
    {
        i = 0;
        while (sorted_env[i])
        {
            declare = ft_split(sorted_env[i], '=');
            if (declare[1])  // Check if there's a value to print
            {
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
            }
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
            parameters = ft_split(prompt[i], '=');
            if (parameters[1])  // Only set if there's a value
            {
                char *trimmed_value = ft_strtrim(parameters[1], "\"");
                set_to_env(parameters[0], trimmed_value, env);
                free(trimmed_value); // Free the trimmed value after usage
            }
            ft_free_matriz(parameters);
        }
    }

    return 0; // Ensure the function returns an integer
}