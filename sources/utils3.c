/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:47:59 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/13 18:58:25 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	calculate_buffer_size(const char *str, const char *op)
{
	size_t	i;
	size_t	count;
	size_t	op_len;

	i = 0;
	count = 0;
	op_len = ft_strlen(op);
	while (str[i])
	{
		if (str[i] == op[0] && ft_strncmp(&str[i], op, op_len) == 0)
		{
			count++;
			i += op_len - 1;
		}
		i++;
	}
	return (ft_strlen(str) + count * (op_len + 2) + 1);
}

size_t	copy_with_quotes(char *result, size_t j, const char *op, char quote)
{
	size_t	i;

	if (!result || !op)
		return (j);
	result[j++] = quote;
	i = 0;
	while (op[i])
		result[j++] = op[i++];
	result[j++] = quote;
	result[j] = '\0';
	return (j);
}

int	update_quotes(int inside_quotes, char current)
{
	if (current == '"' || current == '\'')
		return (!inside_quotes);
	return (inside_quotes);
}

char	*apply_quotes(const char *str, const char *op, char quote, size_t i)
{
	size_t	j;
	int		inside_quotes;
	char	*result;

	result = malloc(calculate_buffer_size(str, op));
	if (!result)
		return (NULL);
	inside_quotes = 0;
	j = 0;
	while (str[i])
	{
		inside_quotes = update_quotes(inside_quotes, str[i]);
		if (!inside_quotes && str[i] == op[0]
			&& ft_strncmp(&str[i], op, ft_strlen(op)) == 0)
		{
			j = copy_with_quotes(result, j, op, quote);
			i += ft_strlen(op) - 1;
		}
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

char	*operator_quotes_and(const char *str, int swift)
{
	if (swift == 0)
		return (apply_quotes(str, "&&", '"', 0));
	else if (swift == 1)
		return (apply_quotes(str, "||", '"', 0));
	else
		return (apply_quotes(str, ";", '\'', 0));
}

int	verify_arrows(const char *s)
{
	int	consecutive = 0;
	int	i = 0;

	while (s[i] != '\0')
	{
		if (s[i] == '<')
		{
			consecutive++;
			if (consecutive > 2)
			{
				printf("Erro: syntax error near unexpected '<<'.\n");
				return (-1);
			}
		}
		else
			consecutive = 0;
		i++;
	}
	return (0);
}

int	exxp(const char *s)
{
	if (verify_arrows(s) == -1)
		return (-1);
	if ((strstr(s, "<<") != NULL && strcmp(s, "<<") == 0) || 
		(strstr(s, "<") != NULL && strcmp(s, "<") == 0))
	{
		printf("Erro: syntax error near unexpected token '%s'.\n", s);
		return (-1);
	}
	return (0);
}