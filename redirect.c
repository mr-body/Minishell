/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:15:03 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/07 20:22:49 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	rredir_cleaner(t_minishell *minishell)
// {

// }

int	redir_trunc_o(t_minishell *minishell)
{
	int		i;
	int		fd;
	char	*tmp;

	ft_memset(minishell->data2, 0, sizeof(minishell->data2));
	split_redirect_command(minishell->redirect_command, minishell->data2, '>');
	if (minishell->args)
		free_data(minishell->args);
	minishell->args = net_args(minishell->data2[0]);
	minishell->fd_type = 0;
	i = 0;
	while (++i < (ft_matriz_len3(minishell->data2) - 1))
	{
		tmp = ft_strtrim(minishell->data2[i], " ");
		fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		close(fd);
		tmp = free_ptr(tmp);
	}
	tmp = ft_strtrim(minishell->data2[ft_matriz_len3(minishell->data2) - 1], " ");
	minishell->fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	tmp = free_ptr(tmp);
	ft_free_matriz2(minishell->data2);
	minishell->is_redir = 1;
	return (0);
}
// verificando se posso tirar o trim do tmp porque pelos visto não é necessário, a string já vem limpa (isso para todas as funcoes de redir)
void	redir_append_o(t_minishell *minishell)
{
	int		i;
	int		fd;
	char	*tmp;

	ft_memset(minishell->data2, 0, sizeof(minishell->data2));
	split_redirect_command(minishell->redirect_command, minishell->data2, '>');
	if (minishell->args)
		free_data(minishell->args);
	minishell->args = net_args(minishell->data2[0]);
	minishell->fd_type = 0;
	i = 0;
	while (++i < (ft_matriz_len3(minishell->data2) - 1))
	{
		printf("data2[i]: %s >> %lu\n", minishell->data2[i], ft_strlen(minishell->data2[i]));
		tmp = ft_strtrim(minishell->data2[i], " ");
		printf("tmp: %s\n", tmp);
		printf("%lu\n", ft_strlen(tmp));
		fd = open(tmp, O_WRONLY | O_CREAT | O_APPEND, 0644);
		close(fd);
		tmp = free_ptr(tmp);
	}
	printf("data2[i]: %s\n", minishell->data2[ft_matriz_len3(minishell->data2) - 1]);
	tmp = ft_strtrim(minishell->data2[ft_matriz_len3(minishell->data2) - 1], " ");
	printf("tmp: %s\n", tmp);
	minishell->fd = open(tmp, O_WRONLY | O_CREAT | O_APPEND, 0644);
	tmp = free_ptr(tmp);
	ft_free_matriz2(minishell->data2);
	minishell->is_redir = 1;
}

// seg fault "< file"
void	redir_trunc_in(t_minishell *minishell)
{
	int		fd;
	char	*tmp;

	ft_memset(minishell->data2, 0, sizeof(minishell->data2));
	split_redirect_command(minishell->redirect_command, minishell->data2, '<');
	if (minishell->args)
		free_data(minishell->args);
	minishell->args = net_args(minishell->data2[0]);
	minishell->fd_type = 1;
	tmp = ft_strtrim(minishell->data2[ft_matriz_len3(minishell->data2) - 1], " ");
	minishell->fd = open(tmp, O_RDONLY);
	tmp = free_ptr(tmp);
	ft_free_matriz2(minishell->data2);
	if (minishell->fd < 0)
	{
		perror("minishell");
		return ;
	}
	minishell->is_redir = 1;
	minishell->is_stdin = 1;
}

void	inset_at_the_heredoc(t_minishell *minishell, t_redirect *var)
{
	while (1)
	{
		var->line = readline("heredoc> ");
		if (ft_strncmp(var->line, var->l_delimiter,
				ft_strlen(var->l_delimiter)) == 0)
			break ;
		var->tmp = ft_strdup("");
		var->line = expand_env_var(var->line, var->tmp, 0);
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
	ft_memset(minishell->data2, 0, sizeof(minishell->data2));
	split_redirect_command(minishell->redirect_command, minishell->data2, '<');
	minishell->args = net_args(minishell->data2[0]);
	minishell->fd_type = 1;
	var.l_delimiter = ft_strtrim(minishell->data2[ft_matriz_len3(minishell->data2)
			- 1], " ");
	var.temp_fd = open(var.temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	inset_at_the_heredoc(minishell, &var);
	var.line = free_ptr(var.line);
	ft_free_matriz2(minishell->data2);
	close(var.temp_fd);
	minishell->fd = open(var.temp_file, O_RDONLY);
	if (minishell->fd < 0)
		return (perror("Could not open temp file for reading"));
	unlink(var.temp_file);
	minishell->is_redir = 1;
	minishell->is_stdin = 1;
}
