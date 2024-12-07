/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 01:59:11 by waalexan          #+#    #+#             */
/*   Updated: 2024/12/07 10:02:52 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*return_cmd_path(char *cmd_path, char **routes)
{
	if (cmd_path == NULL)
	{
		printf("cmd_path: %s\n", cmd_path);
		return (ft_free_matriz(routes), NULL);
	}
	routes = ft_free_matriz(routes);
	printf("cmd_pathps: %s\n", cmd_path);
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
	write(1, "\n", 1);
	rl_on_new_line();
	if (ft_control_prompt(-1) > 1)
	{
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
