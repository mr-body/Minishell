/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 02:04:03 by waalexan          #+#    #+#             */
/*   Updated: 2024/11/08 13:06:57 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_type_quoter(t_util *var, char chr, char delimiter)
{
	if (chr == '"' || chr == '\'')
	{
		if (var->is_quote == 0)
		{
			var->is_quote = 1;
			var->type_quoter = chr;
		}
		else if (chr == var->type_quoter)
		{
			var->is_quote = 0;
		}
		if (delimiter == 32)
		{
			if (chr != var->type_quoter)
				var->temp[var->temp_index++] = chr;
		}
		else
		{
			var->temp[var->temp_index++] = chr;
		}
		return (0);
	}
	return (1);
}

static int	insert_at_the_matriz(t_util *var, char chr, char delimiter)
{
	if (var->is_quote)
	{
		if (var->temp_index < INITIAL_TEMP_SIZE - 1)
			var->temp[var->temp_index++] = chr;
	}
	else if (chr == delimiter)
	{
		if (var->temp_index > 0)
		{
			var->temp[var->temp_index] = '\0';
			var->data->types[var->data->count] = var->type_quoter;
			var->new = expand_env_var(var->temp, ft_strdup(""),
					var->type_quoter);
			var->data->args[var->data->count] = var->new;
			var->data->count++;
			var->temp_index = 0;
		}
	}
	else
	{
		if (var->temp_index < INITIAL_TEMP_SIZE - 1)
			var->temp[var->temp_index++] = chr;
	}
	return (0);
}

static int	last_ajustes(t_util *var)
{
	if (var->temp_index > 0)
	{
		var->temp[var->temp_index] = '\0';
		var->data->types[var->data->count] = var->type_quoter;
		var->new = expand_env_var(var->temp, ft_strdup(""), var->type_quoter);
		if (!var->new)
		{
			free_data(var->data);
			return (-1);
		}
		var->data->args[var->data->count] = var->new;
		var->data->count++;
	}
	var->data->args[var->data->count] = NULL;
	return (0);
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
		return (free(var.data), NULL);
	while (*str)
	{
		if (!set_type_quoter(&var, *str, delimiter))
		{
			str++;
			continue ;
		}
		if (insert_at_the_matriz(&var, *str, delimiter) == -1)
			return (free(var.data), NULL);
		str++;
	}
	if (last_ajustes(&var) == -1)
		return (free(var.data), NULL);
	return (var.data);
}

t_data	*net_args(char *prompt)
{
	return (ft_big_split(prompt, 32));
}
