/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:15:03 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/05 12:38:56 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_trunc_o(t_minishell *minishell)
{
	int		i;
	int		fd;
	char	*tmp;
	char	*delimiter;

	delimiter = ">";
	ft_memset(minishell->data, 0, sizeof(minishell->data));
	ft_strtok(minishell->redirect_command, delimiter, minishell->data);
	if (minishell->args)
		ft_free_matriz(minishell->args);
	minishell->args = net_args(minishell->data[0]);
	printf("=====================================\n");
	ft_print_matriz(minishell->args);
	printf("=====================================\n");
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
	int		fd;
	char	*delimiter;
	char	*line_delimiter;
	char	*temp_file;
	int		temp_fd;
	char	*line;
	char	*tmp;

	line = NULL;
	delimiter = "<<";
	temp_file = "/tmp/heredoc.tmp";
	ft_memset(minishell->data, 0, sizeof(minishell->data));
	ft_strtok(minishell->redirect_command, delimiter, minishell->data);
	minishell->args = net_args(minishell->data[0]);
	minishell->fd_type = 1;
	line_delimiter = ft_strtrim(minishell->data[ft_matriz_len2(minishell->data)
			- 1], " ");
	temp_fd = open(temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		line = readline("heredoc> ");
		if (ft_strncmp(line, line_delimiter, ft_strlen(line_delimiter)) == 0)
			break ;
		tmp = ft_strdup("");
		line = expand_env_var(line, tmp, 0);
		write(temp_fd, line, ft_strlen(line));
		write(temp_fd, "\n", 1);
		line = free_ptr(line);
	}
	line = free_ptr(line);
	close(temp_fd);
	minishell->fd = open(temp_file, O_RDONLY);
	if (minishell->fd < 0)
	{
		perror("Could not open temp file for reading");
		return ;
	}
	unlink(temp_file);
}
