/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<<< HEAD:libft/ft_strtok.c
/*   Created: 2024/11/08 12:15:27 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/08 12:48:18 by gkomba           ###   ########.fr       */
========
/*   Created: 2024/11/07 12:23:40 by waalexan          #+#    #+#             */
/*   Updated: 2024/11/08 13:07:14 by waalexan         ###   ########.fr       */
>>>>>>>> origin/waalexan:util2.c
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

<<<<<<<< HEAD:libft/ft_strtok.c
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
========
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
>>>>>>>> origin/waalexan:util2.c
}
