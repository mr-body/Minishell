/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:03:07 by gkomba            #+#    #+#             */
/*   Updated: 2024/12/09 10:29:17 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	extract_command(t_minishell *minishell, int *redir, int *retrn)
{
	*retrn = 0;
	minishell->args = net_args(minishell->command);
	*redir = is_redir(minishell->command);
	minishell->redirect_command = minishell->command;
	if (!minishell->args)
	{
		free_data(minishell->args);
		*retrn = 1;
		return (1);
	}
	if (!minishell->args->args[0])
	{
		*retrn = 0;
		return (1);
	}
	return (0);
}

void	last_redir(t_minishell *minishell)
{
	int	len;

	len = ft_matriz_len(minishell->raw_args->args);
	if (ft_strchr(minishell->raw_args->args[len - 1], '>')
		|| ft_strchr(minishell->raw_args->args[len - 1], '>'))
		minishell->last = 1;
	else
		minishell->last = 0;
}

int	validate_command(char *input)
{
	int	len;
	int	i;

	i = 1;
	len = ft_strlen(input);
	if ((input[0] == '"' && input[len - 1] == '"') || (input[0] == '\''
			&& input[len - 1] == '\''))
	{
		while (i < len - 1)
		{
			if (ft_isspace(input[i]))
			{
				return (0);
			}
			i++;
		}
		quote_scanner_command(input);
		return (1);
	}
	if (input[0] == '/')
		return (0);
	return (1);
}

void	last_return(t_minishell *minishell, char *str, int pid)
{
	if (ft_strncmp(str, "SUGAR", ft_strlen(str)) == 0)
	{
		signal(SIGINT, handing_c);
		signal(SIGQUIT, handing_c);
		waitpid(pid, &minishell->exit_status, 0);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
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
			minishell->process_out = 1;
		else if (minishell->exit_status == SIGINT)
			minishell->process_out = 130;
		ft_ctrl_c(minishell->process_out);
	}
}

void	last_return_pipe(t_minishell *minishell)
{
	signal(SIGINT, handing_c);
	signal(SIGQUIT, handing_c);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (WIFEXITED(minishell->status))
		minishell->process_out = WEXITSTATUS(minishell->status);
	else if (WIFSIGNALED(minishell->status))
		minishell->process_out = 128 + WTERMSIG(minishell->status);
	else
		minishell->process_out = 1;
	ft_ctrl_c(minishell->status);
}
