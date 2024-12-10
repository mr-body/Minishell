/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:59:09 by gkomba            #+#    #+#             */
/*   Updated: 2024/12/10 12:46:39 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == -1)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

int	redir_to_dir_error(t_minishell *minishell, t_local_data *var)
{
	if (is_directory(var->file))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(var->file, 2);
		ft_putendl_fd(" : Is a directory", 2);
		ft_free_matriz2(minishell->data);
		free(var->file);
		return (minishell->not_flag = -1, ft_ctrl_c(1), 1);
	}
	return (0);
}

int	open_more_fds_append_o(t_minishell *minishell, t_local_data *var)
{
	var->i = 0;
	while (++var->i < (ft_matriz_len3(minishell->data) - 1))
	{
		var->file = quote_scanner(minishell->data[var->i]);
		if (redir_to_dir_error(minishell, var))
			return (1);
		var->fd = open(var->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		close(var->fd);
		free_ptr(var->file);
	}
	var->file = quote_scanner(minishell->data[ft_matriz_len3(minishell->data)
			- 1]);
	if (redir_to_dir_error(minishell, var))
		return (1);
	return (0);
}

int	open_more_fds_trunc_o(t_minishell *minishell, t_local_data *var)
{
	var->i = 0;
	while (++var->i < (ft_matriz_len3(minishell->data) - 1))
	{
		var->file = quote_scanner(minishell->data[var->i]);
		if (redir_to_dir_error(minishell, var))
			return (1);
		var->fd = open(var->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		close(var->fd);
		var->file = free_ptr(var->file);
	}
	var->file = quote_scanner(minishell->data[ft_matriz_len3(minishell->data)
			- 1]);
	if (redir_to_dir_error(minishell, var))
		return (1);
	return (0);
}

int	opne_fds_redir_trunc_in(t_minishell *minishell, t_local_data *var)
{
	if (redir_to_dir_error(minishell, var))
		return (1);
	minishell->fd = open(var->file, O_RDONLY);
	free_ptr(var->file);
	if (minishell->fd < 0)
	{
		ft_free_matriz2(minishell->data);
		ft_ctrl_c(1);
		ft_putendl_fd("minishell: No such file or directory", 2);
		minishell->not_flag = -1;
		return (1);
	}
	return (0);
}
