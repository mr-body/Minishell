/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:30:33 by gkomba            #+#    #+#             */
/*   Updated: 2024/12/10 06:46:53 by gkomba           ###   ########.fr       */
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
	var->i += 2;
	return (get_last_return(tmp));
}

char	*analyze_string(char *arg, char *tmp, t_vars *var)
{
	char	single_char[2];

	ft_memset(single_char, 0, 2);
	var->allow_expand = true;
	while (arg[var->i])
	{
		expander_quotes(arg, var);
		if (allow_expand_condtions(arg, var, 1))
			tmp = expand_last_return(var, tmp);
		else if (allow_expand_condtions(arg, var, 2))
		{
			var->env_var_name = get_env_name(arg, &var->i, &var->k);
			if (var->env_var_name == NULL)
				return (free(tmp), NULL);
			tmp = get_env_value(tmp, var->env_var_name);
			var->i = var->k;
		}
		else
		{
			single_char[0] = arg[var->i];
			tmp = join_single_char(tmp, single_char[0]);
			var->i++;
		}
	}
	return (tmp);
}

char	*expander(char *arg, char *tmp)
{
	t_vars	var;

	ft_memset(&var, 0, sizeof(t_vars));
	return (analyze_string(arg, tmp, &var));
}
