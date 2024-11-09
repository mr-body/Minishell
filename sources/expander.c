/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:30:33 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/09 14:28:41 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_env_name(char *arg, int *j, int *k)
{
	char	*env_var_name;

	*j = *j + 1;
	*k = *j;
	while (arg[*k] && (ft_isalnum(arg[*k]) || arg[*k] == '_'))
	{
		if (arg[*k] == '\"')
			break ;
		*k = *k + 1;
	}
	env_var_name = ft_substr(arg, *j, *k - *j);
	return (env_var_name);
}

static char	*join_single_char(char *tmp, char chr)
{
	char	single_char[2];
	char	*old_tmp;

	single_char[0] = chr;
	single_char[1] = '\0';
	old_tmp = tmp;
	tmp = ft_strjoin(tmp, single_char);
	free(old_tmp);
	return (tmp);
}

static char	*get_env_value(char *tmp, char *env_var_name)
{
	char	*old_tmp;
	char	*env_var_value;

	env_var_value = getenv(env_var_name);
	if (env_var_value)
	{
		old_tmp = tmp;
		tmp = ft_strjoin(tmp, env_var_value);
		free(old_tmp);
	}
	free(env_var_name);
	return (tmp);
}

void	is_on_brace(char *arg, t_vars *var, char *str)
{
	if (ft_strncmp(str, "SUGAR", ft_strlen(str)) == 0)
	{
		if (arg[var->j + 1] == '{')
		{
			var->braces = 1;
			var->j++;
		}
	}
	else if (ft_strncmp(str, "PANCAKE", ft_strlen(str)) == 0)
	{
		if (arg[var->j] == '}' && var->braces == 1)
		{
			var->braces = 0;
			var->j++;
		}
	}
}

char	*expand_env_var(char *arg, char *tmp, char delimiter)
{
	char	single_char[2];
	t_vars	var;

	ft_memset(single_char, 0, 2);
	ft_memset(&var, 0, sizeof(t_vars));
	while (arg[var.j])
	{
		if (arg[var.j] == '$' && delimiter != '\'')
		{
			is_on_brace(arg, &var, "SUGAR");
			var.env_var_name = get_env_name(arg, &var.j, &var.k);
			if (var.env_var_name == NULL)
				return (free(tmp), NULL);
			tmp = get_env_value(tmp, var.env_var_name);
			var.j = var.k;
		}
		else
		{
			is_on_brace(arg, &var, "PANCAKE");
			tmp = join_single_char(tmp, arg[var.j]);
			var.j++;
		}
	}
	ft_delete_chr_on_str(tmp, delimiter);
	return (tmp);
}
