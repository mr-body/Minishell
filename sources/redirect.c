/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:15:03 by gkomba            #+#    #+#             */
/*   Updated: 2024/12/11 18:09:18 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redir_trunc_o(t_minishell *minishell, int type, int index)
{
	t_local_data	var;

	if (redir_trunc_o_aux(minishell))
		return (0);
	ft_memset(minishell->data, 0, sizeof(minishell->data));
	split_redirect_command(minishell->redirect_command, minishell->data);
	if (minishell->args)
		free_data(minishell->args);
	minishell->args = net_args(minishell->data[0]);
	minishell->fd_type = 0;
	if (open_more_fds_trunc_o(minishell, &var))
		return (0);
	minishell->fd = open(var.file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	var.file = free_ptr(var.file);
	ft_redirec_fds(minishell, type, index, 1);
	ft_free_matriz2(minishell->data);
	return (minishell->is_redir = 1, 0);
}

void	redir_append_o(t_minishell *minishell, int type, int index)
{
	t_local_data	var;

	if (redir_append_o_aux(minishell))
		return ;
	ft_memset(minishell->data, 0, sizeof(minishell->data));
	split_redirect_command(minishell->redirect_command, minishell->data);
	if (minishell->args)
		free_data(minishell->args);
	minishell->args = net_args(minishell->data[0]);
	minishell->fd_type = 0;
	if (open_more_fds_append_o(minishell, &var))
		return ;
	minishell->fd = open(var.file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	var.file = free_ptr(var.file);
	ft_redirec_fds(minishell, type, index, 1);
	ft_free_matriz2(minishell->data);
	minishell->is_redir = 1;
}

void	redir_trunc_in(t_minishell *minishell, int type, int index)
{
	t_local_data	var;

	if (redir_trunc_in_aux(minishell))
		return ;
	ft_memset(minishell->data, 0, sizeof(minishell->data));
	split_redirect_command(minishell->redirect_command, minishell->data);
	if (minishell->args)
		free_data(minishell->args);
	minishell->args = net_args(minishell->data[0]);
	minishell->fd_type = 1;
	var.file = quote_scanner(minishell->data[ft_matriz_len3(minishell->data)
			- 1]);
	if (open_fds_redir_trunc_in(minishell, &var))
		return ;
	ft_redirec_fds(minishell, type, index, 0);
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
		if (ft_strcmp(string, var->l) == 0)
			break ;
		tmp = expander(string, ft_strdup(""));
		ft_putendl_fd(tmp, var->fd_in);
		free(tmp);
	}
}

void	redir_append_in(t_minishell *mshell, int type)
{
	t_redirect	var;

	pipe(var.fd);
	var.fd_in = var.fd[1];
	if (redir_append_in_aux(mshell, &var))
		return ;
	ft_memset(mshell->data, 0, sizeof(mshell->data));
	split_redirect_command(mshell->redirect_command, mshell->data);
	if (mshell->args)
		free_data(mshell->args);
	mshell->args = net_args(mshell->data[0]);
	var.file = quote_scanner(mshell->data[ft_matriz_len3(mshell->data) - 1]);
	var.l = ft_strtrim(var.file, " ");
	var.fd_in = var.fd[1];
	var.type = type;
	inset_at_the_heredoc(mshell, &var);
	close(var.fd[1]);
	if (type == 1)
		close_minishell_fd(var.fd[0], STDIN_FILENO);
	mshell->fd = var.fd[0];
	mshell->is_redir = 1;
	mshell->is_stdin = 1;
	free_ptr(var.file);
	free_ptr(var.l);
	ft_free_matriz2(mshell->data);
}
