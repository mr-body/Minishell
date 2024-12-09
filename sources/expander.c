/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:30:33 by gkomba            #+#    #+#             */
/*   Updated: 2024/12/09 21:27:28 by gkomba           ###   ########.fr       */
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
		if (arg[*k] == '\"' || arg[*k] == '\'')
			break ;
		*k = *k + 1;
	}
	env_var_name = ft_substr(arg, *j, *k - *j);
	return (env_var_name);
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

static char	*expand_last_return(t_vars *var, char *tmp)
{
	var->j += 2;
	return (get_last_return(tmp));
}

static char	*expand_env_var(char *arg, char *tmp, t_vars *var)
{
	while (arg[var->j])
	{
		if (arg[var->j] == '$' && arg[var->j + 1] == '?' && var->expand == 1)
			tmp = expand_last_return(var, tmp);
		else if ((arg[var->j] == '$' && arg[var->j + 1] != '\0' && arg[var->j
					+ 1] != '$') && var->expand == 1 && (arg[var->j + 1] != 32
				&& arg[var->j + 1] != '\'') && ft_isdigit(arg[var->j + 1]) == 0)
		{
			is_on_brace(arg, var, "SUGAR");
			var->env_var_name = get_env_name(arg, &var->j, &var->k);
			if (var->env_var_name == NULL)
				return (free(tmp), NULL);
			tmp = get_env_value(tmp, var->env_var_name);
			var->j = var->k;
		}
		else
		{
			is_on_brace(arg, var, "PANCAKE");
			tmp = join_single_char(tmp, arg[var->j]);
			var->j++;
		}
	}
	return (tmp);
}

char	*expander(char *arg, char *tmp)
{
	char	single_char[2];
	t_vars	var;

	ft_memset(single_char, 0, 2);
	ft_memset(&var, 0, sizeof(t_vars));
	var.expand = allow_expand(arg);
	return (expand_env_var(arg, tmp, &var));
}
