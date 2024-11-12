/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 01:59:11 by waalexan          #+#    #+#             */
/*   Updated: 2024/11/09 18:08:13 by gkomba           ###   ########.fr       */
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

int	allow_expand(const char *str)
{
	int	i;
	int	aspas_simples;
	int	aspas_duplas;

	i = 0;
	aspas_simples = 0;
	aspas_duplas = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && !aspas_duplas)
			aspas_simples = !aspas_simples;
		else if (str[i] == '"' && !aspas_simples)
			aspas_duplas = !aspas_duplas;
		if (str[i] == '$' && !aspas_simples && (aspas_duplas || !aspas_duplas))
			return (1);
		i++;
	}
	return (0);
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
