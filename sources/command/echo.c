/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:20:39 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/14 10:20:32 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_is_only_n(char *str)
{
	int	i;

	quote_scanner_command(str);
	if (!str || str[0] != '-')
		return (0);
	if (str[1] != 'n')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static void	ft_print_echo(char **prompt, t_minishell *minishell)
{
	int		i;
	int		n_flag;
	char	*old_line;

	i = 1;
	n_flag = 0;
	while (prompt[i] && ft_is_only_n(prompt[i]) == 1)
	{
		n_flag = 1;
		i++;
	}
	while (prompt[i])
	{
		old_line = prompt[i];
		prompt[i] = quote_scanner(prompt[i]);
		free_ptr(old_line);
		write(minishell->fd, prompt[i], ft_strlen(prompt[i]));
		if (prompt[i + 1])
			write(minishell->fd, " ", 1);
		i++;
	}
	if (!n_flag)
		write(minishell->fd, "\n", 1);
}

int	command_echo(char **prompt, int pipe, t_minishell *minishell)
{
	ft_print_echo(prompt, minishell);
	if (pipe)
	{
		ft_free_matriz(prompt);
		ft_ctrl_c(0);
		minishell->process_out = 0;
		exit(0);
	}
	ft_ctrl_c(0);
	return (minishell->process_out = 0, 0);
}
