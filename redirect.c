/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:15:03 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/05 18:40:03 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct redirect
{
	int		fd;
	char	*tmp;
	char	*delimiter;
	char	*l_delimiter;
	char	*temp_file;
	int		temp_fd;
	char	*line;
}			t_redirect;

int	redir_trunc_o(t_minishell *minishell)
{
	int		i;
	int		fd;
	char	*tmp;
	char	*delimiter;

	delimiter = ">";
	ft_memset(minishell->data, 0, sizeof(minishell->data));
	ft_strtok(minishell->redirect_command, delimiter, minishell->data);
	if (minishell->args)
		free_data(minishell->args);
	minishell->args = net_args(minishell->data[0]);
	minishell->fd_type = 0;
	i = 0;
	while (++i < (ft_matriz_len2(minishell->data) - 1))
	{
		tmp = ft_strtrim(minishell->data[i], " ");
		fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		close(fd);
		tmp = free_ptr(tmp);
	}
	tmp = ft_strtrim(minishell->data[ft_matriz_len2(minishell->data) - 1], " ");
	minishell->fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	tmp = free_ptr(tmp);
	minishell->is_redir = 1;
	return (0);
}

void	redir_append_o(t_minishell *minishell)
{
	int		i;
	int		fd;
	char	*tmp;
	char	*delimiter;

	delimiter = ">>";
	ft_memset(minishell->data, 0, sizeof(minishell->data));
	ft_strtok(minishell->redirect_command, delimiter, minishell->data);
	minishell->args = net_args(minishell->data[0]);
	minishell->fd_type = 0;
	i = 0;
	while (++i < (ft_matriz_len2(minishell->data) - 1))
	{
		tmp = ft_strtrim(minishell->data[i], " ");
		fd = open(tmp, O_WRONLY | O_CREAT | O_APPEND, 0644);
		close(fd);
		tmp = free_ptr(tmp);
	}
	tmp = ft_strtrim(minishell->data[ft_matriz_len2(minishell->data) - 1], " ");
	minishell->fd = open(tmp, O_WRONLY | O_CREAT | O_APPEND, 0644);
	tmp = free_ptr(tmp);
	minishell->is_redir = 1;
}

void	redir_trunc_in(t_minishell *minishell)
{
	int		fd;
	char	*tmp;
	char	*delimiter;

	delimiter = "<";
	ft_memset(minishell->data, 0, sizeof(minishell->data));
	ft_strtok(minishell->redirect_command, delimiter, minishell->data);
	minishell->args = net_args(minishell->data[0]);
	minishell->fd_type = 1;
	tmp = ft_strtrim(minishell->data[ft_matriz_len2(minishell->data) - 1], " ");
	minishell->fd = open(tmp, O_RDONLY);
	tmp = free_ptr(tmp);
	if (minishell->fd < 0)
	{
		perror("minishell");
		return ;
	}
	minishell->is_redir = 1;
}

void	redir_append_in(t_minishell *minishell)
{
	t_redirect	var;

	var.line = NULL;
	var.delimiter = "<<";
	var.temp_file = "/tmp/heredoc.tmp";
	ft_memset(minishell->data, 0, sizeof(minishell->data));
	ft_strtok(minishell->redirect_command, var.delimiter, minishell->data);
	minishell->args = net_args(minishell->data[0]);
	minishell->fd_type = 1;
	var.l_delimiter = ft_strtrim(minishell->data[ft_matriz_len2(minishell->data)
			- 1], " ");
	var.temp_fd = open(var.temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		var.line = readline("heredoc> ");
		if (ft_strncmp(var.line, var.l_delimiter,
				ft_strlen(var.l_delimiter)) == 0)
			break ;
		var.tmp = ft_strdup("");
		var.line = expand_env_var(var.line, var.tmp, 0);
		write(var.temp_fd, var.line, ft_strlen(var.line));
		write(var.temp_fd, "\n", 1);
		var.line = free_ptr(var.line);
	}
	var.line = free_ptr(var.line);
	close(var.temp_fd);
	minishell->fd = open(var.temp_file, O_RDONLY);
	if (minishell->fd < 0)
		return (perror("Could not open temp file for reading"));
	unlink(var.temp_file);
}
