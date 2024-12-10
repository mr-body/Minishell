/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:41:08 by gkomba            #+#    #+#             */
/*   Updated: 2024/12/10 10:26:53 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_if_str_is_pipe(t_minishell *minishell)
{
	if (check_if_str_is_pipe(minishell->check_data) == 1)
	{
		ft_free_matriz(minishell->check_data);
		minishell->exit_status = exec_command_pipe(minishell);
	}
	else
	{
		ft_free_matriz(minishell->check_data);
		minishell->args = net_args(minishell->command);
		if (ft_strlen(minishell->args->args[0]) == 0
			|| ft_is_only(minishell->args->args[0], ' '))
			return (0);
		minishell->exit_status = exec_command(minishell);
	}
	return (1);
}

int	is_not_new(char *value)
{
	extern char	**environ;
	int			i;

	if (!environ)
		return (0);
	i = 0;
	while (environ[i])
	{
		if (!ft_strncmp2(environ[i], value, ft_strlen(value)))
			return (1);
		i++;
	}
	return (0);
}

int	ft_strchr_quote(const char *str, char c)
{
	int	in_s_quotes;
	int	in_d_quotes;

	if (str == NULL)
		return (1);
	in_s_quotes = 0;
	in_d_quotes = 0;
	while (*str)
	{
		ft_in_quotes(*str, &in_d_quotes, &in_s_quotes);
		if (*str == c)
		{
			if (in_s_quotes || in_d_quotes)
				return (1);
			return (0);
		}
		str++;
	}
	return (1);
}

int	is_alphanumeric(const char *str)
{
	while (*str)
	{
		if (!ft_isalnum(*str))
			return (0);
		str++;
	}
	return (1);
}

int	str_is_digit(const char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
