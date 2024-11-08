/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:15:03 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/08 13:10:01 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_trunc_o(t_minishell *minishell)
{
	int	i;
	int	fd;

	ft_memset(minishell->data2, 0, sizeof(minishell->data2));
	split_redirect_command(minishell->redirect_command, minishell->data2, '>');
	if (minishell->args)
		free_data(minishell->args);
	minishell->args = net_args(minishell->data2[0]);
	minishell->fd_type = 0;
	i = 0;
	while (++i < (ft_matriz_len3(minishell->data2) - 1))
	{
		fd = open(minishell->data2[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		close(fd);
	}
	minishell->fd = open(minishell->data2[ft_matriz_len3(minishell->data2) - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_free_matriz2(minishell->data2);
	minishell->is_redir = 1;
	return (0);
}

void	redir_append_o(t_minishell *minishell)
{
	int	i;
	int	fd;

	ft_memset(minishell->data2, 0, sizeof(minishell->data2));
	split_redirect_command(minishell->redirect_command, minishell->data2, '>');
	if (minishell->args)
		free_data(minishell->args);
	minishell->args = net_args(minishell->data2[0]);
	minishell->fd_type = 0;
	i = 0;
	while (++i < (ft_matriz_len3(minishell->data2) - 1))
	{
		fd = open(minishell->data2[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		close(fd);
	}
	minishell->fd = open(minishell->data2[ft_matriz_len3(minishell->data2) - 1],
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	ft_free_matriz2(minishell->data2);
	minishell->is_redir = 1;
}

int	redir_trunc_in(t_minishell *minishell)
{
	int	fd;

	ft_memset(minishell->data2, 0, sizeof(minishell->data2));
	split_redirect_command(minishell->redirect_command, minishell->data2, '<');
	if (minishell->args)
		free_data(minishell->args);
	minishell->args = net_args(minishell->data2[0]);
	minishell->fd_type = 1;
	minishell->fd = open(minishell->data2[ft_matriz_len3(minishell->data2) - 1],
			O_RDONLY);
	ft_free_matriz2(minishell->data2);
	if (minishell->fd < 0)
	{
		perror("minishell");
		minishell->not_flag = -1;
	}
	minishell->is_redir = 1;
	minishell->is_stdin = 1;
}

void	inset_at_the_heredoc(t_minishell *minishell, t_redirect *var)
{
	char	*old_line;

	old_line = NULL;
	while (1)
	{
		var->line = readline("heredoc> ");
		if (ft_strncmp(var->line, var->l_delimiter,
				ft_strlen(var->l_delimiter)) == 0)
			break ;
		var->tmp = ft_strdup("");
		old_line = var->line;
		var->line = expand_env_var(var->line, var->tmp, 0);
		free_ptr(old_line);
		write(var->temp_fd, var->line, ft_strlen(var->line));
		write(var->temp_fd, "\n", 1);
		var->line = free_ptr(var->line);
	}
	if (var->line)
		var->line = free_ptr(var->line);
}

void	redir_append_in(t_minishell *minishell)
{
	t_redirect	var;

	var.line = NULL;
	var.temp_file = "/tmp/heredoc.tmp";
	ft_memset(minishell->data2, 0, sizeof(minishell->data2));
	split_redirect_command(minishell->redirect_command, minishell->data2, '<');
	if (minishell->args)
		free_data(minishell->args);
	minishell->args = net_args(minishell->data2[0]);
	minishell->fd_type = 1;
	var.l_delimiter = ft_strtrim(minishell->data2[ft_matriz_len3(minishell->data2)
			- 1], " ");
	var.temp_fd = open(var.temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	inset_at_the_heredoc(minishell, &var);
	ft_free_matriz2(minishell->data2);
	var.l_delimiter = free_ptr(var.l_delimiter);
	close(var.temp_fd);
	minishell->fd = open(var.temp_file, O_RDONLY);
	if (minishell->fd < 0)
		return (perror("Could not open temp file for reading"));
	unlink(var.temp_file);
	minishell->is_redir = 1;
	minishell->is_stdin = 1;
}
