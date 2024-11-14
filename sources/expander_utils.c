/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:07:52 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/14 10:56:19 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	allow_expand(char *str)
{
	int	i;
	int	aspas_simples;
	int	aspas_duplas;

	i = 0;
	aspas_simples = 0;
	aspas_duplas = 0;
	if (ft_count_chr_occurrency_str(str, '\'') == 1
		|| ft_count_chr_occurrency_str(str, '"') == 1)
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && !aspas_duplas)
			aspas_simples = !aspas_simples;
		else if (str[i] == '"' && !aspas_simples)
			aspas_duplas = !aspas_duplas;
		if (str[i] == '$' && !aspas_simples && (aspas_duplas || !aspas_duplas))
			return (1);
		i++;
	}
	return (0);
}
