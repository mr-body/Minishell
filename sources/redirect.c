/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:15:03 by gkomba            #+#    #+#             */
/*   Updated: 2024/12/07 16:54:31 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redir_trunc_o(t_minishell *minishell, int type)
{
	t_local_data	var;
	char			*file;

	file = NULL;
	if (redir_trunc_o_aux(minishell))
		return (0);
	ft_memset(minishell->data, 0, sizeof(minishell->data));
	split_redirect_command(minishell->redirect_command, minishell->data);
	if (minishell->args)
		free_data(minishell->args);
	minishell->args = net_args(minishell->data[0]);
	minishell->fd_type = 0;
	var.i = 0;
	while (++var.i < (ft_matriz_len3(minishell->data) - 1))
	{
		file = quote_scanner(minishell->data[var.i]);
		var.fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		close(var.fd);
		free_ptr(file);
	}
	file = quote_scanner(minishell->data[ft_matriz_len3(minishell->data) - 1]);
	minishell->fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free_ptr(file);
	if (type == 1)
		close_minishell_fd(minishell->fd, STDOUT_FILENO);
	ft_free_matriz2(minishell->data);
	return (minishell->is_redir = 1, 0);
}

void	redir_append_o(t_minishell *minishell, int type)
{
	t_local_data	var;
	char			*file;

	file = NULL;
	if (redir_append_o_aux(minishell))
		return ;
	ft_memset(minishell->data, 0, sizeof(minishell->data));
	split_redirect_command(minishell->redirect_command, minishell->data);
	if (minishell->args)
		free_data(minishell->args);
	minishell->args = net_args(minishell->data[0]);
	minishell->fd_type = 0;
	var.i = 0;
	while (++var.i < (ft_matriz_len3(minishell->data) - 1))
	{
		file = quote_scanner(minishell->data[var.i]);
		var.fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		close(var.fd);
		free_ptr(file);
	}
	file = quote_scanner(minishell->data[ft_matriz_len3(minishell->data) - 1]);
	minishell->fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	free_ptr(file);
	if (type == 1)
		close_minishell_fd(minishell->fd, STDOUT_FILENO);
	ft_free_matriz2(minishell->data);
	minishell->is_redir = 1;
}

void	redir_trunc_in(t_minishell *minishell, int type)
{
	char	*file;

	file = NULL;
	if (redir_trunc_in_aux(minishell))
		return ;
	ft_memset(minishell->data, 0, sizeof(minishell->data));
	split_redirect_command(minishell->redirect_command, minishell->data);
	if (minishell->args)
		free_data(minishell->args);
	minishell->args = net_args(minishell->data[0]);
	minishell->fd_type = 1;
	file = quote_scanner(minishell->data[ft_matriz_len3(minishell->data) - 1]);
	minishell->fd = open(file, O_RDONLY);
	free_ptr(file);
	if (minishell->fd < 0)
	{
		ft_free_matriz2(minishell->data);
		ft_ctrl_c(1);
		ft_putendl_fd("minishell: No such file or directory", 2);
		minishell->not_flag = -1;
	}
	if (type == 1)
		close_minishell_fd(minishell->fd, STDIN_FILENO);
	ft_free_matriz2(minishell->data);
	minishell->is_redir = 1;
	minishell->is_stdin = 1;
}

void	inset_at_the_heredoc(t_minishell *minishell, t_redirect *var)
{
	char	string[700];
	char	*tmp;
	int		byte;

	(void)minishell;
	control_center();
	while (1)
	{
		byte = read(0, string, 700);
		if (byte == 0)
			break ;
		if (string[byte - 1] == '\n')
			string[byte - 1] = '\0';
		if (strcmp(string, var->l) == 0)
			break ;
		tmp = expander(string, ft_strdup(""));
		ft_putendl_fd(tmp, var->fd_in);
		free(tmp);
	}
}

void	redir_append_in(t_minishell *minishell, int type)
{
	t_redirect	var;
	char	*file;

	file = NULL;
	pipe(var.fd);
	var.fd_in = var.fd[1];
	if (redir_append_in_aux(minishell, &var))
		return ;
	ft_memset(minishell->data, 0, sizeof(minishell->data));
	split_redirect_command(minishell->redirect_command, minishell->data);
	if (minishell->args)
		free_data(minishell->args);
	minishell->args = net_args(minishell->data[0]);
	file = quote_scanner(minishell->data[ft_matriz_len3(minishell->data) - 1]);
	var.l = ft_strtrim(file, " ");
	var.fd_in = var.fd[1];
	var.type = type;
	inset_at_the_heredoc(minishell, &var);
	close(var.fd[1]);
	if (type == 1)
		close_minishell_fd(var.fd[0], STDIN_FILENO);
	minishell->fd = var.fd[0];
	minishell->is_redir = 1;
	minishell->is_stdin = 1;
	free_ptr(file);
	free_ptr(var.l);
	ft_free_matriz2(minishell->data);
}
