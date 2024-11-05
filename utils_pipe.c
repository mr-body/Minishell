/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 02:12:13 by waalexan          #+#    #+#             */
/*   Updated: 2024/11/05 16:04:31 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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