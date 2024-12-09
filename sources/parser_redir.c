/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:34:32 by gkomba            #+#    #+#             */
/*   Updated: 2024/12/09 21:25:47 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	finalize_argument(t_split_redir_cmd *vars, char **data)
{
	if (vars->current_arg[0] != '\0')
	{
		if (vars->is_redirect)
		{
			vars->data_idx++;
			data[vars->data_idx] = malloc(ft_strlen(vars->current_arg) + 1);
			if (data[vars->data_idx])
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

static void	save_curr_arg(t_split_redir_cmd *vars, char **data)
{
	if (vars->is_redirect)
	{
		vars->data_idx++;
		if (data[vars->data_idx] != NULL)
		{
			free(data[vars->data_idx]);
			data[vars->data_idx] = NULL;
		}
		data[vars->data_idx] = (char *)malloc(ft_strlen(vars->current_arg) + 1);
		if (!data[vars->data_idx])
			return ;
		ft_strcpy(data[vars->data_idx], vars->current_arg);
		vars->is_redirect = false;
	}
	else
		ft_strcat_no_malloc(data[0], vars->current_arg);
	vars->current_arg[0] = '\0';
}

static void	split_redir(t_split_redir_cmd *vars, char *command, char **data)
{
	while (command[vars->i] != '\0')
	{
		ft_in_quotes(command[vars->i], &vars->in_s_quotes, &vars->in_d_quotes);
		if ((!vars->in_s_quotes && !vars->in_d_quotes)
			&& (command[vars->i] == '<' || command[vars->i] == '>'))
		{
			finalize_argument(vars, data);
			vars->is_redirect = true;
			vars->i++;
			continue ;
		}
		if ((!vars->in_s_quotes && !vars->in_d_quotes)
			&& command[vars->i] == ' ')
		{
			finalize_argument(vars, data);
			vars->i++;
			continue ;
		}
		ft_strncat(vars->current_arg, &command[vars->i], 1);
		vars->i++;
	}
}

void	split_redirect_command(char *command, char **data)
{
	t_split_redir_cmd	vars;
	int					i;
	char				*tmp;

	ft_memset(&vars, 0, sizeof(t_split_redir_cmd));
	vars.current_arg = (char *)malloc(sizeof(char) * ft_strlen(command) + 1);
	if (!vars.current_arg)
		return ;
	vars.current_arg[0] = '\0';
	data[0] = (char *)malloc(sizeof(char) * ft_strlen(command) + 1);
	data[0][0] = '\0';
	split_redir(&vars, command, data);
	if (vars.current_arg[0] != '\0')
		save_curr_arg(&vars, data);
	free(vars.current_arg);
	i = 0;
	while (data[i] != NULL)
	{
		tmp = data[i];
		data[i] = expander(data[i], ft_strdup(""));
		free(tmp);
		i++;
	}
}
