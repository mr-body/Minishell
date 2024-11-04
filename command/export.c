/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 22:18:49 by waalexan          #+#    #+#             */
/*   Updated: 2024/11/04 22:19:45 by waalexan         ###   ########.fr       */
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

void	ft_delete_quotes(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
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

int	command_export(char **prompt, int pipe, t_minishell *minishell)
{
	extern char	**environ;
	char		**sorted_env;
	char		*output;
	char		*var;
	int			i;

	i = 0;
	if (!prompt[1])
	{
		sorted_env = sort_env(environ);
		while (sorted_env[i])
		{
			output = ft_strjoin("declare -x ", sorted_env[i]);
			ft_putendl_fd(output, 1);
			free(output);
			i++;
		}
	}
	else
	{
		i = 0;
		while (prompt[++i])
		{
			var = ft_strdup(prompt[i]);
			ft_delete_quotes(var);
			set_to_env(ft_get_env(var));
			free(var);
		}
	}
	if (pipe)
	{
		ft_free_matriz(prompt);
		exit(0);
	}
	return (0);
}
