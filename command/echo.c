/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:20:39 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/09 11:10:04 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_only_n(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[0] != '-')
		return (0);
	if (str[0] == '-' && !str[1])
		return (0);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	command_echo(char **prompt, int pipe, t_minishell *minishell)
{
	int	i;
	int	n_flag;

	i = 0;
	n_flag = ft_is_only_n(prompt[1]);
	if (n_flag == 1)
		i++;
	while (prompt[++i])
	{
		if (ft_strncmp(prompt[i], "?", 1) == 0)
			ft_putnbr_fd(minishell->process_out, minishell->fd);
		else
			write(minishell->fd, prompt[i], ft_strlen(prompt[i]));
		if (prompt[i + 1])
			write(minishell->fd, " ", 1);
	}
	if (n_flag == 0)
		write(minishell->fd, "\n", 1);
	if (pipe)
	{
		ft_free_matriz(prompt);
		minishell->process_out = 0;
		exit(0);
	}
	return (minishell->process_out = 0, 0);
}
