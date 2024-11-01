/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:15:03 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/01 10:31:58 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_heredoc(char *line_delimiter);

void	redir_trunc_o(t_minishell *minishell)
{
	int		i;
	int		fd;
	char	*tmp;
	char	*delimiter;

	delimiter = ">";
	ft_memset(minishell->data, 0, sizeof(minishell->data));
	ft_strtok(minishell->readline, delimiter, minishell->data);
	minishell->command = minishell->data[0];
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
	if (strchr(minishell->command, '|'))
		exec_command_pipe(minishell);
	else
		exec_command(minishell);
}

void	redir_append_o(t_minishell *minishell)
{
	int		i;
	int		fd;
	char	*tmp;
	char	*delimiter;

	delimiter = ">>";
	ft_memset(minishell->data, 0, sizeof(minishell->data));
	ft_strtok(minishell->readline, delimiter, minishell->data);
	minishell->command = minishell->data[0];
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
	if (strchr(minishell->command, '|'))
		exec_command_pipe(minishell);
	else
		exec_command(minishell);
}

void	redir_trunc_in(t_minishell *minishell)
{
	int		fd;
	char	*tmp;
	char	*delimiter;

	delimiter = "<";
	ft_memset(minishell->data, 0, sizeof(minishell->data));
	ft_strtok(minishell->readline, delimiter, minishell->data);
	minishell->command = minishell->data[0];
	minishell->fd_type = 1;
	tmp = ft_strtrim(minishell->data[ft_matriz_len2(minishell->data) - 1], " ");
	minishell->fd = open(tmp, O_RDONLY);
	tmp = free_ptr(tmp);
	if (minishell->fd < 0)
	{
		perror("minishell");
		return ;
	}
	if (strchr(minishell->command, '|'))
		exec_command_pipe(minishell);
	else
		exec_command(minishell);
}

void	redir_append_in(t_minishell *minishell)
{
	char	*delimiter;
	char	*line_delimiter;
	char	*temp_file;

	delimiter = "<<";
	temp_file = "/tmp/heredoc.tmp";
	ft_memset(minishell->data, 0, sizeof(minishell->data));
	ft_strtok(minishell->readline, delimiter, minishell->data);
	minishell->command = minishell->data[0];
	minishell->fd_type = 1;
	line_delimiter = ft_strtrim(minishell->data[ft_matriz_len2(minishell->data)
			- 1], " ");
	ft_heredoc(line_delimiter);
	minishell->fd = open(temp_file, O_RDONLY);
	if (minishell->fd < 0)
	{
		perror("Could not open temp file for reading");
		return ;
	}
	if (ft_strchr(minishell->command, '|'))
		exec_command_pipe(minishell);
	else
		exec_command(minishell);
	unlink(temp_file);
}

static void	ft_heredoc(char *line_delimiter)
{
	int		fd;
	char	*tmp;
	char	*line_tmp;
	char	*line;

	fd = open("/tmp/heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		line = readline("heredoc> ");
		if (ft_strncmp(line, line_delimiter, ft_strlen(line_delimiter)) == 0)
			break ;
		tmp = ft_strdup("");
		line_tmp = expand_env_var(line, tmp);
		write(fd, line_tmp, ft_strlen(line_tmp));
		write(fd, "\n", 1);
		line = free_ptr(line);
		line_tmp = free_ptr(line_tmp);
	}
	line = free_ptr(line);
	line_delimiter = free_ptr(line_delimiter);
	close(fd);
}
