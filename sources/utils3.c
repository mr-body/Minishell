/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:47:59 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/15 12:17:17 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redir_sintx(char *input, t_sintax *sintax)
{
	if (sintax->state == 1)
		return (redir_syntax_error("SUGAR"), 2);
	sintax->state = 1;
	if (input[sintax->i + 1] == input[sintax->i])
		sintax->i++;
	sintax->i++;
	if (input[sintax->i] == '>' || input[sintax->i] == '<')
		return (redir_syntax_error("PANCAKE"), 2);
	return (1);
}

int	pipe_sintx(char *input, t_sintax *sintax)
{
	
	if (sintax->state == 2)
		return (pipe_syntax_error("SUGAR"), 2);
	sintax->state = 2;
	if (input[sintax->i + 1] == '|')
		return (pipe_syntax_error("PANCAKE"), 2);
	sintax->i++;
	return (1);
}

int	validate_sintax_aux(char *input, t_sintax *sintax)
{
	if ((input[sintax->i] == '<' || input[sintax->i] == '>') && !sintax->in_quotes)
	{
		if (redir_sintx(input, sintax) == 2)
			return (2);
	}
	else if ((input[sintax->i] == '|') && !sintax->in_quotes)
	{
		if (pipe_sintx(input, sintax) == 2)
			return (2);
	}
	else
	{
		sintax->state = 0;
		sintax->i++;
	}
	return (1);
}

int	validate_sintax(char *input)
{
	t_sintax	sintax;

	ft_memset(&sintax, 0, sizeof(t_sintax));
	while (input[sintax.i])
	{
		ft_in_quotes(input[sintax.i], &sintax.in_quotes);
		if (ft_isspace(input[sintax.i]))
		{
			sintax.i++;
			continue ;
		}
		if (validate_sintax_aux(input, &sintax) == 2)
			return (2);
	}
	return (1);
}

int	ft_prompt(t_minishell *minishell)
{
	if (minishell->gkomba)
	{
		minishell->readline = readline(AMARELO "gkomba" VERDE "🧐> " RESET);
		minishell->waalexan = 0;
		minishell->ms = 0;
		return (1);
	}
	else if (minishell->waalexan)
	{
		minishell->readline = readline(AMARELO "Waalexan" VERDE "😎> " RESET);
		minishell->gkomba = 0;
		minishell->ms = 0;
		return (1);
	}
	else if (minishell->ms)
	{
		minishell->readline = readline("minishell# ");
		minishell->waalexan = 0;
		minishell->gkomba = 0;
		return (0);
	}
	return (1);
}

int	unclosed_quotes(const char *str)
{
	int	single_quotes;
	int	double_quotes;
	int	i;

	single_quotes = 0;
	double_quotes = 0;
	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '\'' && !double_quotes)
			single_quotes = !single_quotes;
		else if (str[i] == '\"' && !single_quotes)
			double_quotes = !double_quotes;
	}
	if (single_quotes || double_quotes)
	{
		ft_putendl_fd("syntax error: unexpected end of file", 2);
		ft_ctrl_c(2);
		return (1);
	}
	return (0);
}
