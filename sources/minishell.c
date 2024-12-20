/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 01:59:39 by waalexan          #+#    #+#             */
/*   Updated: 2024/12/11 17:50:40 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_control_prompt(int value)
{
	static int	status = 0;

	if (value != -1)
		status = value;
	return (status);
}

void	ft_epur_str(char *str)
{
	t_epur_vars	var;

	ft_memset(&var, 0, sizeof(t_epur_vars));
	while (str[var.i])
	{
		ft_in_quotes(str[var.i], &var.in_d_quotes, &var.in_s_quotes);
		if (ft_isspace(str[var.i]) && !var.in_d_quotes && !var.in_s_quotes)
		{
			if (!var.prev_space && !var.in_d_quotes && !var.in_s_quotes)
				str[var.j++] = ' ';
			var.prev_space = 1;
			var.i++;
		}
		else
		{
			var.prev_space = 0;
			if (str[var.i] == '\t' && !var.in_d_quotes && !var.in_s_quotes)
				str[var.i] = ' ';
			str[var.j++] = str[var.i++];
		}
	}
	if (var.j > 0 && str[var.j - 1] == ' ')
		var.j--;
	str[var.j] = '\0';
}

int	execute_command(t_minishell *minishell)
{
	minishell->fd = STDOUT_FILENO;
	minishell->fd_type = 1;
	if (unclosed_quotes(minishell->readline) == 1)
		return (1);
	minishell->check_data = ft_split_ms(minishell->readline, ' ');
	if (minishell->check_data[0] == NULL)
		return (ft_free_matriz(minishell->check_data), 0);
	if (whitespace_and_syntax(minishell, minishell->check_data) != 0)
		return (0);
	if (ft_check_last_pipe(minishell->readline) == 1)
		get_extra_prompt(minishell);
	minishell->command = minishell->readline;
	minishell->redirect_command = minishell->readline;
	if (!ft_send_to_execute(minishell))
		return (free_data(minishell->args), 0);
	return (minishell->exit_status);
}

static void	get_readline(t_minishell *minishell)
{
	minishell->readline = readline("minishell# ");
	if (!minishell->readline)
	{
		free(minishell->readline);
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	else if (minishell->readline && !ft_is_only(minishell->readline, '\n'))
		add_history(minishell->readline);
	ft_epur_str(minishell->readline);
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
	ft_control_prompt(2);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_sigint);
		get_readline(&minishell);
		free(minishell.readline);
		ft_control_prompt(2);
	}
	return (0);
}
