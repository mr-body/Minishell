/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:26:22 by gkomba            #+#    #+#             */
/*   Updated: 2024/12/14 23:32:32 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_long_long_overflow(const char *nptr)
{
	long long	value;

	value = ft_atoi_v2(nptr);
	if (value == LLONG_MAX || value == LLONG_MIN)
		return (1);
	return (0);
}

static int	check_exit_syntax(char **prompt)
{
	if (prompt[1] == NULL)
		return (1);
	else if (prompt[1])
	{
		if (prompt[1][0] == '-' && ft_isdigit(prompt[1][1]))
			return (1);
		if (str_is_digit(prompt[1]) && prompt[2] == NULL)
			return (1);
		if (!ft_isdigit(prompt[1][0]) && prompt[1][0] != '-')
			return (2);
		if (is_alphanumeric(prompt[1]) && !str_is_digit(prompt[1]))
			return (2);
		else
			return (0);
	}
	else
		return (0);
}

void	get_exit(char **prompt)
{
	long long	i;

	i = 0;
	if (prompt[1])
	{
		if (check_long_long_overflow(prompt[1]))
		{
			ft_putendl_fd("exit: numeric argument required", 2);
			ft_free_matriz(prompt);
			exit(2);
		}
		i = ft_atoi_v2(prompt[1]);
		if (i < 0 || i > 255)
			i = i % 256;
		if (i < 0)
			i += 256;
		ft_free_matriz(prompt);
		exit(i);
	}
	else
	{
		ft_free_matriz(prompt);
		exit(i);
	}
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
		get_exit(prompt);
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
