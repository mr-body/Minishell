/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:15:03 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/22 13:11:00 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			free(var->line);
			break ;
		}
		var->tmp = ft_strdup("");
		old_line = var->line;
		var->line = expander(var->line, var->tmp);
		free_ptr(old_line);
		ft_putendl_fd(var->line, var->temp_fd);
		var->line = free_ptr(var->line);
	}
}

// void	epur_str(char *str)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == ' ' && str[i + 1] == ' ')
// 			i++;
// 		str[j] = str[i];
// 		i++;
// 		j++;
// 	}
// 	str[j] = '\0';
// }

void	redir_append_in(t_minishell *minishell, int type)
{
	t_redirect	var;
	// char		string[700];
	int			fd[2];
	// int			byte;
	// char		*deli;
	// char		*tmp;

	pipe(fd);
	var.line = NULL;
	var.temp_file = "/tmp/heredoc.tmp";
	if (redir_append_in_aux(minishell, &var))
		return ;
	ft_memset(minishell->data, 0, sizeof(minishell->data));
	split_redirect_command(minishell->redirect_command, minishell->data, '<');
	if (minishell->args)
		free_data(minishell->args);
	minishell->args = net_args(minishell->data[0]);
	printf("data: %s\n", minishell->data[ft_matriz_len3(minishell->data) - 1]);
	if (minishell->data[ft_matriz_len3(minishell->data) - 1] != NULL)
		var.l_delimit = ft_strtrim(minishell->data[ft_matriz_len3(minishell->data) - 1],
			" ");
	inset_at_the_heredoc(&var);
	close(fd[1]);
	if (type == 1)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	minishell->fd = fd[0];
	minishell->is_redir = 1;
	minishell->is_stdin = 1;
	ft_free_matriz2(minishell->data);
	var.l_delimit = free_ptr(var.l_delimit);
	// free(deli);
}
