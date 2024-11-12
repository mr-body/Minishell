/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:15:03 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/12 17:14:37 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redir_trunc_o(t_minishell *minishell)
{
	int	i;
	int	fd;

	ft_memset(minishell->data, 0, sizeof(minishell->data));
	split_redirect_command(minishell->redirect_command, minishell->data, '>');
	if (minishell->args)
		free_data(minishell->args);
	minishell->args = net_args(minishell->data[0]);
	minishell->fd_type = 0;
	i = 0;
	while (++i < (ft_matriz_len3(minishell->data) - 1))
	{
		fd = open(minishell->data[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		close(fd);
	}
	minishell->fd = open(minishell->data[ft_matriz_len3(minishell->data) - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_free_matriz2(minishell->data);
	minishell->is_redir = 1;
	return (0);
}

void	redir_append_o(t_minishell *minishell)
{
	int	i;
	int	fd;

	ft_memset(minishell->data, 0, sizeof(minishell->data));
	split_redirect_command(minishell->redirect_command, minishell->data, '>');
	if (minishell->args)
		free_data(minishell->args);
	minishell->args = net_args(minishell->data[0]);
	minishell->fd_type = 0;
	i = 0;
	while (++i < (ft_matriz_len3(minishell->data) - 1))
	{
		fd = open(minishell->data[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		close(fd);
	}
	minishell->fd = open(minishell->data[ft_matriz_len3(minishell->data) - 1],
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	ft_free_matriz2(minishell->data);
	minishell->is_redir = 1;
}

void	redir_trunc_in(t_minishell *minishell)
{
	ft_memset(minishell->data, 0, sizeof(minishell->data));
	split_redirect_command(minishell->redirect_command, minishell->data, '<');
	if (ft_matriz_len3(minishell->data) == 0)
	{
		ft_free_matriz2(minishell->data);
		redir_trunc_in_case_one(minishell, minishell->redirect_command);
		return ;
	}
	if (minishell->args)
		free_data(minishell->args);
	minishell->args = net_args(minishell->data[0]);
	minishell->fd_type = 1;
	minishell->fd = open(minishell->data[ft_matriz_len3(minishell->data) - 1],
			O_RDONLY);
	if (minishell->fd < 0)
	{
		free_data(minishell->args);
		ft_free_matriz2(minishell->data);
		ft_ctrl_c(1);
		ft_putendl_fd("minishell: No such file or directory", 2);
		minishell->not_flag = -1;
	}
	ft_free_matriz2(minishell->data);
	minishell->is_redir = 1;
	minishell->is_stdin = 1;
}

void	inset_at_the_heredoc(t_redirect *var)
{
	char	*old_line;

	old_line = NULL;
	while (1)
	{
		var->line = readline("heredoc> ");
		if (!var->line)
		{
			free(var->line);
			break ;
		}
		if (ft_strcmp(var->line, var->l_delimit) == 0)
		{
			printf("heredoc");
			free(var->line);
			break ;
		}
		var->tmp = ft_strdup("");
		old_line = var->line;
		var->line = expander(var->line, var->tmp);
		free_ptr(old_line);
		write(var->temp_fd, var->line, ft_strlen(var->line));
		write(var->temp_fd, "\n", 1);
		var->line = free_ptr(var->line);
	}
}

void	redir_append_in(t_minishell *minishell)
{
	t_redirect	var;

	var.line = NULL;
	var.temp_file = "/tmp/heredoc.tmp";
	ft_memset(minishell->data, 0, sizeof(minishell->data));
	split_redirect_command(minishell->redirect_command, minishell->data, '<');
	if (ft_matriz_len3(minishell->data) == 0)
	{
		ft_free_matriz2(minishell->data);
		redir_append_in_case_one(minishell, var);
		return ;
	}
	if (minishell->args)
		free_data(minishell->args);
	minishell->args = net_args(minishell->data[0]);
	minishell->fd_type = 1;
	var.l_delimit = ft_strtrim(minishell->data[ft_matriz_len3(minishell->data)
			- 1], " ");
	var.temp_fd = open(var.temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	inset_at_the_heredoc(&var);
	ft_free_matriz2(minishell->data);
	var.l_delimit = free_ptr(var.l_delimit);
	close(var.temp_fd);
	minishell->fd = open(var.temp_file, O_RDONLY);
	if (minishell->fd < 0)
		return (ft_ctrl_c(1), perror("Could not open temp file for reading"));
	unlink(var.temp_file);
	minishell->is_redir = 1;
	minishell->is_stdin = 1;
}
