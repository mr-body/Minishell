/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 01:59:11 by waalexan          #+#    #+#             */
/*   Updated: 2024/11/09 16:53:37 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	allow_expand(const char *str)
{
	int	i;
	int	aspas_simples;
	int	aspas_duplas;

	i = 0;
	aspas_simples = 0;
	aspas_duplas = 0;
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
