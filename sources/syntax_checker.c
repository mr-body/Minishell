/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:35:50 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/14 10:36:20 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	verify_pipes_syntax(t_minishell *minishell)
{
	int	i;

	i = 0;
	minishell->verify_syntax = ft_split_ms(minishell->command, ' ');
	while (minishell->verify_syntax[i])
	{
		if (ft_strncmp(minishell->verify_syntax[i], "|", 1) == 0)
		{
			if (minishell->verify_syntax[i + 1] == NULL)
			{
				pipe_syntax_error("SUGAR");
				ft_free_matriz(minishell->verify_syntax);
				return (2);
			}
			if (ft_strncmp(minishell->verify_syntax[i + 1], "|", 1) == 0)
			{
				pipe_syntax_error("PANCAKE");
				return (ft_free_matriz(minishell->verify_syntax), 2);
			}
		}
		i++;
	}
	return (ft_free_matriz(minishell->verify_syntax), 0);
}

int	verify_redir_syntax_one(t_minishell *minishell, char *redir_type)
{
	int	i;

	i = -1;
	if (return_redir_type(redir_type[0], redir_type[1]) != R_TRUNC_O
		&& return_redir_type(redir_type[0], redir_type[1]) != R_TRUNC_I)
		return (0);
	minishell->verify_syntax = ft_split_ms(minishell->redirect_command, ' ');
	if (redir_is_not_followed_by_pipe(minishell->verify_syntax))
		return (ft_free_matriz(minishell->verify_syntax), 2);
	while (minishell->verify_syntax[++i])
	{
		if (ft_strncmp(minishell->verify_syntax[i], redir_type,
				ft_strlen(redir_type)) == 0)
		{
			if (check_redir_one(minishell, i, redir_type) == 2)
				return (ft_free_matriz(minishell->verify_syntax), 2);
		}
	}
	return (ft_free_matriz(minishell->verify_syntax), 0);
}

int	verify_redir_syntax_two(t_minishell *minishell, char *redir_type)
{
	int	i;

	i = -1;
	if (return_redir_type(redir_type[0], redir_type[1]) != R_APPEND_I
		&& return_redir_type(redir_type[0], redir_type[1]) != R_APPEND_O)
		return (0);
	minishell->verify_syntax = ft_split_ms(minishell->redirect_command, ' ');
	if (redir_is_not_followed_by_pipe(minishell->verify_syntax))
		return (ft_free_matriz(minishell->verify_syntax), 2);
	while (minishell->verify_syntax[++i])
	{
		if (ft_strncmp(minishell->verify_syntax[i], redir_type,
				ft_strlen(redir_type)) == 0)
		{
			if (check_redir_two(minishell, i, redir_type) == 2)
				return (ft_free_matriz(minishell->verify_syntax), 2);
		}
	}
	return (ft_free_matriz(minishell->verify_syntax), 0);
}

int	check_name_var_syntax(char *var)
{
	int	i;

	i = 0;
	if (ft_isdigit(var[i]) || var[i] == '=')
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(var, 2);
		ft_putendl_fd(" :not a valid identifier", 2);
		return (ft_ctrl_c(1), 1);
	}
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_' && var[i] != '"'
			&& var[i] != '\'')
		{
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd(var, 2);
			ft_putendl_fd(" :not a valid identifier", 2);
			return (ft_ctrl_c(1), 1);
		}
		i++;
	}
	return (0);
}

int	syntax_checker(t_minishell *minishell)
{
	minishell->status = validate_sintax(minishell->command);
	if (minishell->status == 2)
		return (2);
	minishell->exit_status = verify_pipes_syntax(minishell);
	if (minishell->exit_status == 2)
		return (2);
	minishell->status = verify_redir_syntax_one(minishell, ">");
	if (minishell->status == 2)
		return (2);
	minishell->status = verify_redir_syntax_one(minishell, "<");
	if (minishell->status == 2)
		return (2);
	minishell->status = verify_redir_syntax_two(minishell, "<<");
	if (minishell->status == 2)
		return (2);
	minishell->status = verify_redir_syntax_two(minishell, ">>");
	if (minishell->status == 2)
		return (2);
	return (0);
}