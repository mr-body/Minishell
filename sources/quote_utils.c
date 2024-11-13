/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:39:46 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/13 16:59:06 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_delete_quotes_on_matriz(char **prompt)
{
	int	i;

	i = -1;
	while (prompt[++i])
	{
		ft_delete_chr_on_str(prompt[i], '\'');
		ft_delete_chr_on_str(prompt[i], '\"');
	}
}

void	ft_in_quotes(char c, int *in_quotes)
{
	if (c == '"' || c == '\'')
		*in_quotes = !*in_quotes;
}

void	quote_scanner_command(char *input)
{
	char	current_quote;
	int		read_pos;
	int		write_pos;

	current_quote = 0;
	read_pos = 0;
	write_pos = 0;
	while (input[read_pos] != '\0')
	{
		if ((input[read_pos] == '\'' || input[read_pos] == '"')
			&& current_quote == 0)
		{
			current_quote = input[read_pos];
		}
		else if (input[read_pos] == current_quote)
			current_quote = 0;
		else
			input[write_pos++] = input[read_pos];
		read_pos++;
	}
	input[write_pos] = '\0';
}

void	quote_delete(t_quotes *vars, const char *input)
{
	while (input[vars->read_pos] != '\0')
	{
		if ((input[vars->read_pos] == '\'' || input[vars->read_pos] == '"'))
		{
			if (vars->current_quote == 0)
				vars->current_quote = input[vars->read_pos];
			else if (input[vars->read_pos] == vars->current_quote)
			{
				vars->current_quote = 0;
				vars->read_pos++;
				continue ;
			}
			else
				vars->output[vars->write_pos++] = input[vars->read_pos];
		}
		else
			vars->output[vars->write_pos++] = input[vars->read_pos];
		vars->read_pos++;
	}
}

char	*quote_scanner(const char *input)
{
	t_quotes	vars;

	vars.len = ft_strlen(input);
	vars.output = (char *)malloc(vars.len + 1);
	if (vars.output == NULL)
		return (perror("Erro de alocação de memória"), NULL);
	vars.current_quote = 0;
	vars.read_pos = 0;
	vars.write_pos = 0;
	quote_delete(&vars, input);
	if (vars.current_quote != 0)
	{
		vars.read_pos = 0;
		vars.write_pos = 0;
		while (input[vars.read_pos] != '\0')
			vars.output[vars.write_pos++] = input[vars.read_pos++];
	}
	vars.output[vars.write_pos] = '\0';
	return (vars.output);
}
