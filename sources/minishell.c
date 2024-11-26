/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 01:59:39 by waalexan          #+#    #+#             */
/*   Updated: 2024/11/26 14:54:59 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	execute_command(t_minishell *minishell)
{
	char	**data;

	minishell->fd = STDOUT_FILENO;
	minishell->fd_type = 1;
	if (unclosed_quotes(minishell->readline) == 1)
		return (1);
	data = ft_split_ms(minishell->readline, ' ');
	if (data[0] == NULL)
		return (ft_free_matriz(data), 0);
	minishell->command = minishell->readline;
	minishell->redirect_command = minishell->readline;
	if (whitespace_and_syntax(minishell, data) != 0)
		return (0);
	if (check_if_str_is_pipe(data) == 1)
	{
		ft_free_matriz(data);
		minishell->exit_status = exec_command_pipe(minishell);
	}
	else
	{
		ft_free_matriz(data);
		minishell->args = net_args(minishell->command);
		minishell->exit_status = exec_command(minishell);
	}
	return (0);
}

static void	get_readline(t_minishell *minishell)
{
	ft_prompt(minishell);
	if (!minishell->readline)
	{
		free(minishell->readline);
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	if (is_new_prompt(minishell) == 0)
		return ;
	else if (minishell->readline && !ft_is_only(minishell->readline, '\n'))
		add_history(minishell->readline);
	execute_command(minishell);
}

int	main(int argc, char **argv)
{
	t_minishell	minishell;

	if (argc != 1)
	{
		ft_putstr_fd("Error: No arguments needed\n", 2);
		exit(1);
	}
	(void)argv;
	ft_ctrl_c(1);
	ft_memset(&minishell, 0, sizeof(t_minishell));
	increment_shell_level(&minishell);
	minishell.ms = 1;
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_sigint);
		get_readline(&minishell);
		free(minishell.readline);
	}
	return (0);
}
