/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:26:22 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/10 16:50:50 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_exit_syntax(char **prompt)
{
	if (prompt[1] == NULL)
		return (1);
	else if (prompt[1])
	{
		if (ft_isdigit(prompt[1][0]) && prompt[2] == NULL)
			return (1);
		if (!ft_isdigit(prompt[1][0]))
			return (2);
		else
			return (0);
	}
	else
		return (0);
}

static int	ft_exit(char *planet, char **prompt, int pipe,
		t_minishell *minishell)
{
	if (ft_strncmp(planet, "JUPITER", ft_strlen(planet)) == 0)
	{
		if (pipe)
			return (ft_free_matriz(prompt), minishell->process_out = 0,
				ft_ctrl_c(0), 0);
		ft_putendl_fd("exit", 1);
		ft_free_matriz(prompt);
		exit(0);
	}
	else if (ft_strncmp(planet, "SATURNO", ft_strlen(planet)) == 0)
	{
		if (pipe)
		{
			ft_putendl_fd("exit: numeric argument required", 2);
			return (ft_free_matriz(prompt), minishell->process_out = 0,
				ft_ctrl_c(2), 0);
		}
		ft_putendl_fd("exit", 1);
		ft_putendl_fd("exit: numeric argument required", 2);
		ft_free_matriz(prompt);
		exit(2);
	}
	return (0);
}

int	command_exit(char **prompt, int pipe, t_minishell *minishell)
{
	int	retrn;

	retrn = check_exit_syntax(prompt);
	if (retrn == 1)
		return (ft_exit("JUPITER", prompt, pipe, minishell));
	else if (retrn == 2)
		return (ft_exit("SATURNO", prompt, pipe, minishell));
	else
	{
		ft_putendl_fd("exit: too many arguments", 1);
		minishell->process_out = 1;
		return (ft_ctrl_c(1), 1);
	}
}
