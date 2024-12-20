/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_case_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:58:48 by gkomba            #+#    #+#             */
/*   Updated: 2024/12/10 11:55:33 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redir_to_dir_error_case_one(t_minishell *minishell, char **tmp, char *tmp2)
{
	if (is_directory(tmp2))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(tmp2, 2);
		ft_putendl_fd(" : Is a directory", 2);
		ft_free_matriz(tmp);
		free_ptr(tmp2);
		return (minishell->not_flag = -1, ft_ctrl_c(1), 1);
	}
	return (0);
}

void	redir_trunc_o_case_one(t_minishell *minishell)
{
	char	**tmp;
	char	*tmp2;

	tmp = ft_split_ms(minishell->redirect_command, '>');
	tmp2 = ft_strtrim(tmp[0], " ");
	if (redir_to_dir_error_case_one(minishell, tmp, tmp2))
		return ;
	minishell->fd = open(tmp2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free_ptr(tmp2);
	if (minishell->fd < 0)
	{
		ft_free_matriz(tmp);
		ft_ctrl_c(1);
		ft_putendl_fd("could not open/create/read file", 2);
		minishell->not_flag = -1;
		return ;
	}
	ft_free_matriz(tmp);
	ft_ctrl_c(0);
	minishell->is_redir = 1;
	minishell->not_flag = -1;
	return ;
}

void	redir_append_o_case_one(t_minishell *minishell)
{
	char	**tmp;
	char	*tmp2;

	tmp = ft_split_ms(minishell->redirect_command, '>');
	tmp2 = ft_strtrim(tmp[0], " ");
	if (redir_to_dir_error_case_one(minishell, tmp, tmp2))
		return ;
	minishell->fd = open(tmp2, O_WRONLY | O_CREAT | O_APPEND, 0644);
	free_ptr(tmp2);
	if (minishell->fd < 0)
	{
		ft_free_matriz(tmp);
		ft_ctrl_c(1);
		ft_putendl_fd("could not open/create/read file", 2);
		minishell->not_flag = -1;
		return ;
	}
	ft_free_matriz(tmp);
	ft_ctrl_c(0);
	minishell->is_redir = 1;
	minishell->not_flag = -1;
	return ;
}

void	redir_trunc_in_case_one(t_minishell *minishell, int one)
{
	char	**tmp;
	char	*tmp2;

	tmp = ft_split_ms(minishell->redirect_command, '<');
	if (one == 1)
		tmp2 = ft_strtrim(tmp[1], " ");
	else
		tmp2 = ft_strtrim(tmp[0], " ");
	minishell->fd = open(tmp2, O_RDONLY);
	free_ptr(tmp2);
	if (minishell->fd < 0)
	{
		ft_free_matriz(tmp);
		ft_ctrl_c(1);
		ft_putendl_fd("minishell: No such file or directory", 2);
		minishell->not_flag = -1;
		return ;
	}
	minishell->is_redir = 1;
	minishell->not_flag = -1;
	minishell->is_stdin = 1;
	ft_ctrl_c(0);
	ft_free_matriz(tmp);
	return ;
}

void	redir_append_in_case_one(t_minishell *minishell, t_redirect *var,
		int one)
{
	char	**tmp;

	tmp = ft_split_ms(minishell->redirect_command, '<');
	if (one == 1)
		var->l = ft_strtrim(tmp[1], " ");
	else
		var->l = ft_strtrim(tmp[0], " ");
	ft_free_matriz(tmp);
	inset_at_the_heredoc(minishell, var);
	var->l = free_ptr(var->l);
	if (minishell->fd < 0)
		return (ft_ctrl_c(1), perror("Could not open temp file for reading"));
	minishell->is_redir = 1;
	minishell->is_stdin = 1;
	minishell->not_flag = -1;
	ft_ctrl_c(0);
}
