/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 02:12:13 by waalexan          #+#    #+#             */
/*   Updated: 2024/12/10 10:26:47 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	open_fds(t_minishell *minishell, int nbr_cmds)
{
	int	i;

	i = 0;
	while (i < nbr_cmds - 1)
	{
		if (pipe(minishell->pipe_fds + i * 2) < 0)
			perror("pipe error");
		i++;
	}
}

void	close_fds(t_minishell *minishell, int nbr_cmds)
{
	int	i;

	if (!minishell->pipe_fds)
		return ;
	i = 0;
	while (i < 2 * (nbr_cmds - 1))
	{
		close(minishell->pipe_fds[i]);
		i++;
	}
}

void	ft_exit_process(t_minishell *minishell, int nbr_cmds)
{
	close_fds(minishell, nbr_cmds);
	minishell->pipe_fds = (int *)free_ptr((char *)minishell->pipe_fds);
	free_data(minishell->raw_args);
}

int	ft_is_only(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}

int	check_if_str_is_pipe(char **matriz)
{
	int		i;

	i = -1;
	while (matriz[++i])
	{
		if (ft_strchr_quote(matriz[i], '|') == 0)
			return (1);
	}
	return (0);
}
