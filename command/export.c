/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 22:18:49 by waalexan          #+#    #+#             */
/*   Updated: 2024/11/06 14:16:46 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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

void	set_to_env(char *value)
{
	extern char	**environ;
	static char	*new_env[700000];
	int			i;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp2(environ[i], value, ft_strlen(value)) == 0)
		{
			environ[i] = value;
			return ;
		}
		i++;
	}
	i = 0;
	while (environ[i])
	{
		new_env[i] = environ[i];
		i++;
	}
	new_env[i] = value;
	new_env[i + 1] = NULL;
	environ = new_env;
}

char	*ft_get_env(char *var_name)
{
	extern char	**environ;
	static char	new_env[700000];
	static int	i;
	char		*tmp;
	int			j;

	j = 0;
	if (var_name != NULL)
	{
		while (var_name[j])
		{
			new_env[i] = var_name[j];
			i++;
			j++;
		}
		new_env[i] = '\0';
	}
	tmp = &new_env[i - j];
	i++;
	return (tmp);
}

int	export_var(char **prompt)
{
	int	i;
	char		*var;
	i = 0;
	while (prompt[++i])
	{
		if (check_name_var_syntax(prompt[i]))
			return (1);
		var = ft_strdup(prompt[i]);
		ft_delete_quotes(var);
		set_to_env(ft_get_env(var));
		free(var);
	}
	return (0);
}

int	export_print(void)
{
	extern char	**environ;
	int	i;
	char	*output;
	char	**sorted_env;
	
	i = 0;
	sorted_env = sort_env(environ);
	while (sorted_env[i])
	{
		output = ft_strjoin("declare -x ", sorted_env[i]);
		ft_putendl_fd(output, 1);
		free(output);
		i++;
	}
	return (0);
}

int	command_export(char **prompt, int pipe, t_minishell *minishell)
{
	if (!prompt[1])
		minishell->exit_status = export_print();
	else
		minishell->exit_status = export_var(prompt);
	if (pipe)
	{
		ft_free_matriz(prompt);
		exit(0);
	}
	return (0);
}
