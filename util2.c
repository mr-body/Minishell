/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:23:40 by waalexan          #+#    #+#             */
/*   Updated: 2024/11/07 12:25:42 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tonkenize(char *str, char *delimiter,
		char result[MAX_WORDS][MAX_WORD_LENGTH], t_util *var)
{
	while (str[var->i])
	{
		if (ft_strchr(delimiter, str[var->i]))
		{
			if (var->in_word)
			{
				result[var->j][var->k] = '\0';
				var->j++;
				var->k = 0;
				var->in_word = 0;
			}
		}
		else
		{
			if (var->k < MAX_WORD_LENGTH - 1)
				result[var->j][var->k++] = str[var->i];
			var->in_word = 1;
		}
		var->i++;
	}
}

void	ft_strtok(char *str, char *delimiter,
		char result[MAX_WORDS][MAX_WORD_LENGTH])
{
	t_util	var;

	ft_memset(&var, 0, sizeof(t_util));
	tonkenize(str, delimiter, result, &var);
	if (var.in_word)
	{
		result[var.j][var.k] = '\0';
		var.j++;
	}
	while (var.j < MAX_WORDS)
		result[var.j++][0] = '\0';
}

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->count)
	{
		free(data->args[i]);
	}
	free(data->args);
	free(data->types);
	free(data);
}
