/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 01:59:11 by waalexan          #+#    #+#             */
/*   Updated: 2024/12/10 12:43:01 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	get_extra_prompt(t_minishell *minishell)
{
	char	*herepipe;

	while (ft_check_last_pipe(minishell->readline) == 1)
	{
		herepipe = readline("> ");
		if (!herepipe)
		{
			free(minishell->readline);
			ft_putendl_fd("syntax error: unexpected end of file", 2);
			ft_putendl_fd("exit", 1);
			exit(2);
		}
		minishell->temp = minishell->readline;
		minishell->readline = ft_strjoin(minishell->readline, herepipe);
		if (minishell->readline && !ft_is_only(minishell->readline, '\n'))
			add_history(minishell->readline);
		free(minishell->temp);
		free(herepipe);
	}
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
