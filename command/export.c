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
void set_to_env(char *value, char **environ) {
    int i = 0;
    // Look for the variable in the environment
    while (environ[i]) {
        i++;
    }

    // Variable not found, add it to the end
    environ[i] = value;
    environ[i + 1] = NULL; // Ensure the last element is NULL
}

 void	ft_delete_quotes(char *str)
 {
	 int i = 0;
	 int j = 0;
	 while (str[i])
	 {
		 if (str[i] != '\"')
		 {
			 str[j] = str[i];
			 j++;
		 }
		 i++;
	 }
	 str[j] = '\0';
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
			ft_delete_quotes(prompt[i]);
			printf("prompt[%d]: %s\n", i, prompt[i]);
			set_to_env(prompt[1], environ);
		}
	}
	if (pipe)
	{
		ft_free_matriz(prompt);
		exit(0);
	}
	return (0);
}