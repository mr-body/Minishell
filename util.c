/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 02:04:03 by waalexan          #+#    #+#             */
/*   Updated: 2024/11/06 16:37:50 by gkomba           ###   ########.fr       */
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

t_data	*ft_big_split(char *str, char delimiter)
{
	t_util	var;

	ft_memset(&var, 0, sizeof(t_util));
	var.data = malloc(sizeof(t_data));
	if (!var.data)
		return (NULL);
	var.data->count = 0;
	var.data->args = malloc(INITIAL_ARG_COUNT * sizeof(char *));
	var.data->types = malloc(INITIAL_ARG_COUNT * sizeof(char));
	if (!var.data->args || !var.data->types)
	{
		return (free(var.data), NULL);
	}
	while (*str)
	{
		if (*str == '"' || *str == '\'')
		{
			if (var.is_quote == 0)
			{
				var.is_quote = 1;
				var.type_quoter = *str;
			}
			else if (*str == var.type_quoter)
				var.is_quote = 0;
			if (delimiter == 32)
			{
				if (*str != var.type_quoter)
					var.temp[var.temp_index++] = *str;
			}
			else
				var.temp[var.temp_index++] = *str;
			str++;
			continue ;
		}
		if (var.is_quote)
		{
			if (var.temp_index < INITIAL_TEMP_SIZE - 1)
				var.temp[var.temp_index++] = *str;
		}
		else if (*str == delimiter)
		{
			if (var.temp_index > 0)
			{
				var.temp[var.temp_index] = '\0';
				var.data->types[var.data->count] = var.type_quoter;
				var.new = expand_env_var(var.temp, ft_strdup(""),
						var.type_quoter);
				var.data->args[var.data->count] = var.new;
				if (!var.new)
					return (free_data(var.data), NULL);
				var.data->count++;
				var.temp_index = 0;
			}
		}
		else
		{
			if (var.temp_index < INITIAL_TEMP_SIZE - 1)
				var.temp[var.temp_index++] = *str;
		}
		str++;
	}
	if (var.temp_index > 0)
	{
		var.temp[var.temp_index] = '\0';
		var.data->types[var.data->count] = var.type_quoter;
		var.new = expand_env_var(var.temp, ft_strdup(""), var.type_quoter);
		var.data->args[var.data->count] = var.new;
		if (!var.new)
			return (free_data(var.data), NULL);
		var.data->count++;
	}
	var.data->args[var.data->count] = NULL;
	return (var.data);
}

t_data	*net_args(char *prompt)
{
	t_data	*data;

	data = ft_big_split(prompt, 32);
	return (data);
}
