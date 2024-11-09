/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_sms.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 01:59:11 by waalexan          #+#    #+#             */
/*   Updated: 2024/11/09 16:36:50 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_command_error(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	ft_print_syntax_error(void)
{
	ft_putendl_fd("minishell: syntax error: quote", 2);
}

void	invalid_char_error(char c)
{
	ft_ctrl_c(2);
	ft_putendl_fd("minishell: invalid character ", 2);
	ft_putchar_fd(c, 2);
	ft_putchar_fd('\n', 2);
}

void	redir_syntax_error(char *str)
{
	ft_ctrl_c(2);
	if (ft_strncmp(str, "SUGAR", ft_strlen(str)) == 0)
	{
		ft_putendl_fd("syntax error near unexpected token `newline'", 2);
	}
	else if (ft_strncmp(str, "PANCAKE", ft_strlen(str)) == 0)
	{
		ft_putendl_fd("syntax error near unexpected token `|'", 2);
	}
}

void	pipe_syntax_error(char *str)
{
	ft_ctrl_c(2);
	if (ft_strncmp(str, "SUGAR", ft_strlen(str)) == 0)
	{
		ft_putendl_fd("syntax error near unexpected token `newline'", 2);
	}
	else if (ft_strncmp(str, "PANCAKE", ft_strlen(str)) == 0)
	{
		ft_putendl_fd("syntax error near unexpected token `|'", 2);
	}
}
