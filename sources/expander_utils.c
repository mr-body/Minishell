/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:07:52 by gkomba            #+#    #+#             */
/*   Updated: 2024/12/11 12:51:57 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	is_on_brace(char *arg, t_vars *var, char *str)
{
	if (ft_strncmp(str, "SUGAR", ft_strlen(str)) == 0)
	{
		if (arg[var->i + 1] == '{')
		{
			var->braces = 1;
			var->i++;
		}
	}
	else if (ft_strncmp(str, "PANCAKE", ft_strlen(str)) == 0)
	{
		if (arg[var->i] == '}' && var->braces == 1)
		{
			var->braces = 0;
			var->i++;
		}
	}
}

char	*get_last_return(char *tmp)
{
	char	*old_tmp;
	char	*return_value;

	return_value = ft_itoa(ft_ctrl_c(-1));
	old_tmp = tmp;
	tmp = ft_strjoin(tmp, return_value);
	free(old_tmp);
	free(return_value);
	return (tmp);
}

char	*join_single_char(char *tmp, char chr)
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

int	allow_expand_condtions(char *arg, t_vars *var, int swicth)
{
	if (swicth == 1)
	{
		if (arg[var->i] == '$' && arg[var->i + 1] == '?'
			&& var->allow_expand == 1)
			return (1);
	}
	else if (swicth == 2)
	{
		if (arg[var->i] == '$' && arg[var->i + 1] != '\0'
			&& var->allow_expand == 1 && (ft_isalpha(arg[var->i + 1])
				|| arg[var->i + 1] == '_'))
			return (1);
	}
	return (0);
}

void	expander_quotes(char *arg, t_vars *var)
{
	if (arg[var->i] == '\'')
	{
		if (!var->in_d_quotes)
		{
			var->in_s_quotes = !var->in_s_quotes;
			var->allow_expand = !var->in_s_quotes;
		}
	}
	else if (arg[var->i] == '\"')
	{
		var->in_d_quotes = !var->in_d_quotes;
		var->allow_expand = (var->in_d_quotes || !var->in_s_quotes);
	}
	if (var->in_d_quotes)
	{
		var->allow_expand = true;
	}
}
