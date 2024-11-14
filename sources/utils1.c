/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 01:59:11 by waalexan          #+#    #+#             */
/*   Updated: 2024/11/14 10:53:21 by gkomba           ###   ########.fr       */
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

	i = -1;
	while (++i < data->count)
	{
		free(data->args[i]);
	}
	free(data->args);
	free(data->types);
	free(data);
}

void	last_return(t_minishell *minishell, char *str, int pid)
{
	if (ft_strncmp(str, "SUGAR", ft_strlen(str)) == 0)
	{
		signal(SIGINT, handing_c);
		waitpid(pid, &minishell->exit_status, 0);
		signal(SIGINT, SIG_IGN);
		if (WIFEXITED(minishell->exit_status))
			minishell->process_out = WEXITSTATUS(minishell->exit_status);
		else if (WIFSIGNALED(minishell->exit_status))
			minishell->process_out = 128 + WTERMSIG(minishell->exit_status);
		else
			minishell->process_out = 1;
	}
	else if (ft_strncmp(str, "PANCAKE", ft_strlen(str)) == 0)
	{
		if (minishell->exit_status == 256)
			minishell->process_out = 127;
		else if (minishell->exit_status == SIGINT)
			minishell->process_out = 130;
		ft_ctrl_c(minishell->process_out);
	}
}

void	last_return_pipe(t_minishell *minishell)
{
	signal(SIGINT, handing_c);
	signal(SIGINT, SIG_IGN);
	if (WIFEXITED(minishell->status))
		minishell->process_out = WEXITSTATUS(minishell->status);
	else if (WIFSIGNALED(minishell->status))
		minishell->process_out = 128 + WTERMSIG(minishell->status);
	else
		minishell->process_out = 1;
}

int	is_new_prompt(t_minishell *minishell)
{
	if (ft_strcmp(minishell->readline, "gkomba") == 0)
	{
		minishell->gkomba = 1;
		minishell->waalexan = 0;
		minishell->ms = 0;
		return (ft_prompt_sms('g'), 0);
	}
	else if (ft_strcmp(minishell->readline, "waalexan") == 0)
	{
		minishell->waalexan = 1;
		minishell->gkomba = 0;
		minishell->ms = 0;
		return (ft_prompt_sms('w'), 0);
	}
	else if (ft_strcmp(minishell->readline, "ms") == 0
		&& (minishell->waalexan == 1 || minishell->gkomba == 1))
	{
		minishell->ms = 1;
		minishell->waalexan = 0;
		minishell->gkomba = 0;
		return (ft_prompt_sms('m'), 0);
	}
	return (1);
}
