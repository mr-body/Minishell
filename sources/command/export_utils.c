/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:09:37 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/09 12:34:00 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_env(char *var_name)
{
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
