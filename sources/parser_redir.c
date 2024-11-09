/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:34:32 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/08 12:53:12 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	in_quotes(t_split_redir_cmd *vars, char *command)
{
	if (command[vars->i] == '"' || command[vars->i] == '\'')
	{
		vars->in_quotes = !vars->in_quotes;
		vars->i++;
		return (1);
	}
	return (0);
}

void	save_curr_arg(t_split_redir_cmd *vars, char **data)
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

void	split_redir(t_split_redir_cmd *vars, char *command, char **data,
		char delimiter)
{
	while (command[vars->i] != '\0')
	{
		if (in_quotes(vars, command))
			continue ;
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
			continue ;
		}
		if (!vars->in_quotes && command[vars->i] == ' ')
		{
			finalize_argument(vars, data);
			vars->i++;
			continue ;
		}
		ft_strncat(vars->current_arg, &command[vars->i], 1);
		vars->i++;
	}
}

void	split_redirect_command(char *command, char **data, char delimiter)
{
	t_split_redir_cmd	vars;

	ft_memset(&vars, 0, sizeof(t_split_redir_cmd));
	vars.current_arg = (char *)malloc(sizeof(char) * ft_strlen(command) + 1);
	if (!vars.current_arg)
		return ;
	vars.current_arg[0] = '\0';
	data[0] = (char *)malloc(sizeof(char) * ft_strlen(command) + 1);
	data[0][0] = '\0';
	split_redir(&vars, command, data, delimiter);
	if (vars.current_arg[0] != '\0')
		save_curr_arg(&vars, data);
	free(vars.current_arg);
}
