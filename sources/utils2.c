/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:41:08 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/13 18:01:33 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redir_is_not_followed_by_pipe(char **matriz)
{
	int	i;

	i = 0;
	while (matriz[i])
	{
		if (ft_strncmp(matriz[i], "<|", 2) == 0)
		{
			redir_syntax_error("PANCAKE");
			return (1);
		}
		else if (ft_strncmp(matriz[i], "<<|", 3) == 0)
		{
			redir_syntax_error("PANCAKE");
			return (1);
		}
		i++;
	}
	return (0);
}

int	in_quotes(t_split_redir_cmd *vars, char *command)
{
	if (command[vars->i] == '"' || command[vars->i] == '\'')
	{
		vars->in_quotes = !vars->in_quotes;
		vars->i++;
		return (1);
	}
	return (0);
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
	return (1);
}

void	ft_prompt_sms(char c)
{
	if (c == 'g')
		ft_putendl_fd(AZUL "gkomba >> Welcome Human 🪐" RESET, 1);
	else if (c == 'w')
		ft_putendl_fd( VERDE "waalexa >> Now. Waalexan is on control 🌍" RESET, 1);
	else if (c == 'm')
		ft_putendl_fd(AMARELO "minishell >> Welcome to minishell 🌌" RESET, 1);
}