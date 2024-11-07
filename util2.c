/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:23:40 by waalexan          #+#    #+#             */
/*   Updated: 2024/11/07 19:16:59 by gkomba           ###   ########.fr       */
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

typedef struct s_split_redir_cmd
{
	int data_idx;
	int in_quotes;
	int is_redirect;
	char *current_arg;
	int	i;
} t_split_redir_cmd;

void	finalize_argument(t_split_redir_cmd *vars, char **data)
{
	if (vars->current_arg[0] != '\0')
	{
		if (vars->is_redirect)
		{
			vars->data_idx++;
			data[vars->data_idx] = malloc(ft_strlen(vars->current_arg) + 1);
			ft_strcpy(data[vars->data_idx], vars->current_arg);
			vars->is_redirect = false;
		}
		else
		{
			ft_strcat_no_malloc(data[0], vars->current_arg);
			ft_strcat_no_malloc(data[0], " ");
		}
		vars->current_arg[0] = '\0';
	}
}

void save_curr_arg(t_split_redir_cmd *vars, char **data)
{
	if (vars->is_redirect)
	{
		vars->data_idx++;
		data[vars->data_idx] = (char *)malloc(ft_strlen(vars->current_arg) + 1);
		ft_strcpy(data[vars->data_idx], vars->current_arg);
	}
	else
		ft_strcat_no_malloc(data[0], vars->current_arg);
}

void	split_redir(t_split_redir_cmd *vars, char *command, char **data, char delimiter)
{
	while (command[vars->i] != '\0')
	{
		if (command[vars->i] == '"' || command[vars->i] == '\'')
		{
			vars->in_quotes = !vars->in_quotes;
			vars->i++;
			continue;
		}
		if (!vars->in_quotes && command[vars->i] == delimiter)
		{
			if (vars->current_arg[0] != '\0')
			{
				ft_strcat_no_malloc(data[0], vars->current_arg);
				ft_strcat_no_malloc(data[0], " ");
				vars->current_arg[0] = '\0';
			}
			vars->is_redirect = 1;
			vars->i++;
			continue;
		}
		if (!vars->in_quotes && command[vars->i] == ' ')
		{
			finalize_argument(vars, data);
			vars->i++;
			continue;
		}
		ft_strncat(vars->current_arg, &command[vars->i], 1);
		vars->i++;
	}
}

void	split_redirect_command(char *command, char **data, char delimiter)
{
	t_split_redir_cmd vars;

	ft_memset(&vars, 0, sizeof(t_split_redir_cmd));
	vars.current_arg = (char *)malloc(sizeof(char) * ft_strlen(command) + 1);
	if (!vars.current_arg)
		return;
	vars.current_arg[0] = '\0';
	data[0] = (char *)malloc(sizeof(char) * ft_strlen(command) + 1);
	data[0][0] = '\0';
	split_redir(&vars, command, data, delimiter);
	if (vars.current_arg[0] != '\0')
		save_curr_arg(&vars, data);
	free(vars.current_arg);
}
