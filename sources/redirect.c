/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:15:03 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/22 15:20:02 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_ctrl_c;

int	redir_trunc_o(t_minishell *minishell, int type)
{
	int	i;
	int	fd;

	if (redir_trunc_o_aux(minishell))
		return (0);
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
	if (type == 1)
	{
		dup2(minishell->fd, STDOUT_FILENO);
		close(minishell->fd);
	}
	ft_free_matriz2(minishell->data);
	minishell->is_redir = 1;
	return (0);
}

void	redir_append_o(t_minishell *minishell, int type)
{
	int	i;
	int	fd;

	if (redir_append_o_aux(minishell))
		return ;
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
	if (type == 1)
	{
		dup2(minishell->fd, STDOUT_FILENO);
		close(minishell->fd);
	}
	ft_free_matriz2(minishell->data);
	minishell->is_redir = 1;
}

void	redir_trunc_in(t_minishell *minishell, int type)
{
	if (redir_trunc_in_aux(minishell))
		return ;
	ft_memset(minishell->data, 0, sizeof(minishell->data));
	split_redirect_command(minishell->redirect_command, minishell->data, '<');
	if (minishell->args)
		free_data(minishell->args);
	minishell->args = net_args(minishell->data[0]);
	minishell->fd_type = 1;
	minishell->fd = open(minishell->data[ft_matriz_len3(minishell->data) - 1],
			O_RDONLY);
	if (minishell->fd < 0)
	{
		ft_free_matriz2(minishell->data);
		ft_ctrl_c(1);
		ft_putendl_fd("minishell: No such file or directory", 2);
		minishell->not_flag = -1;
	}
	if (type == 1)
	{
		dup2(minishell->fd, STDIN_FILENO);
		close(minishell->fd);
	}
	ft_free_matriz2(minishell->data);
	minishell->is_redir = 1;
	minishell->is_stdin = 1;
}

void	close_ctrl_c2(int signal)
{
	(void)signal;
	g_ctrl_c = 1;
}

void	ignore_signal(int signal)
{
	(void)signal;
}

void	inset_at_the_heredoc(t_minishell *minishell, t_redirect *var)
{
	char		string[700];
	char		*tmp;
	int			byte;

	signal(SIGINT, close_ctrl_c2);
	signal(SIGQUIT, ignore_signal);
	g_ctrl_c = 0;
	while (1)
	{
		byte = read(0, string, 700);
		if (g_ctrl_c)
		{
			minishell->not_flag = -1;
			if (var->type)
				exit(130);
			break ;
		}
		if (byte == 0)
			break ;
		if (string[byte - 1] == '\n')
			string[byte - 1] = '\0';
		if (strcmp(string, var->l_delimit) == 0)
			break ;
		tmp = expander(string, ft_strdup(""));
		ft_putendl_fd(tmp, var->fd_in);
		free(tmp);
	}
}

void	redir_append_in(t_minishell *minishell, int type)
{
	t_redirect	var;
	
	int			fd[2];

	pipe(fd);
	if (redir_append_in_aux(minishell, &var))
		return ;
	ft_memset(minishell->data, 0, sizeof(minishell->data));
	split_redirect_command(minishell->redirect_command, minishell->data, '<');
	if (minishell->args)
		free_data(minishell->args);
	minishell->args = net_args(minishell->data[0]);
	var.l_delimit = ft_strtrim(minishell->data[ft_matriz_len3(minishell->data) - 1],
			" ");
	var.fd_in = fd[1];
	var.type = type;
	inset_at_the_heredoc(minishell, &var);
	close(fd[1]);
	if (type == 1)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	minishell->fd = fd[0];
	minishell->is_redir = 1;
	minishell->is_stdin = 1;
	free_ptr(var.l_delimit);
	ft_free_matriz2(minishell->data);
}