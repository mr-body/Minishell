/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 01:59:11 by waalexan          #+#    #+#             */
/*   Updated: 2024/12/02 15:06:21 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*return_cmd_path(char *cmd_path, char **routes)
{
	if (cmd_path == NULL)
		return (ft_free_matriz(routes), NULL);
	routes = ft_free_matriz(routes);
	if (invalid_path(cmd_path))
	{
		free(cmd_path);
		return (NULL);
	}
	return (cmd_path);
}

void	handing_c(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n", 1);
}

void	free_data(t_data *data)
{
	int	i;

	if (!data)
		return ;
	i = -1;
	while (++i < data->count)
	{
		free(data->args[i]);
	}
	free(data->args);
	free(data->types);
	free(data);
}

int	ft_ctrl_c(int value)
{
	static int	status = 0;

	if (value != -1)
		status = value;
	return (status);
}

void	handle_sigint(int signal)
{
	(void)signal;
	ft_ctrl_c(130);
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	if (ft_ctrl_c(-1))
		rl_redisplay();
}
