
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 02:13:12 by waalexan          #+#    #+#             */
/*   Updated: 2024/11/05 02:13:13 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(char *str)
{
	int		i;
	int		is_quote;
	char	quote_type;

	i = 0;
	is_quote = 0;
	quote_type = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (!is_quote)
			{
				is_quote = 1;
				quote_type = str[i];
			}
			else if (str[i] == quote_type)
			{
				is_quote = 0;
			}
			i++;
			continue ;
		}
		if (!is_quote)
		{
			if (str[i] == '>' && str[i + 1] == '>')
				return (R_APPEND_O);
			else if (str[i] == '<' && str[i + 1] == '<')
				return (R_APPEND_I);
			else if (str[i] == '>')
				return (R_TRUNC_O);
			else if (str[i] == '<')
				return (R_TRUNC_I);
		}
		i++;
	}
	return (0);
}

int	is_redirout(char *str)
{
	char	**mat;
	int		i;

	mat = ft_split(str, 32);
	i = -1;
	while (mat[++i])
	{
		if (ft_strlen(mat[i]) == 1)
		{
			ft_free_matriz(mat);
			return (R_TRUNC_O);
		}
		else if (ft_strlen(mat[i]) == 2 && ft_strncmp(mat[i], ">>", 2) == 0)
		{
			ft_free_matriz(mat);
			return (R_APPEND_O);
		}
	}
	ft_free_matriz(mat);
	return (0);
}

int	is_redirin(char *str)
{
	char	**mat;
	int		i;

	mat = ft_split(str, 32);
	i = -1;
	while (mat[++i])
	{
		if (ft_strlen(mat[i]) == 1 && ft_strncmp(mat[i], "<", 1) == 0)
		{
			ft_free_matriz(mat);
			return (R_TRUNC_I);
		}
		else if (ft_strlen(mat[i]) == 2 && ft_strncmp(mat[i], ">>", 2) == 0)
		{
			ft_free_matriz(mat);
			return (R_APPEND_I);
		}
	}
	ft_free_matriz(mat);
	return (0);
}

int	ft_find_little_str(char *str, char *little)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!little)
		return (0);
	while (str[i])
	{
		if (str[i] == little[j])
		{
			while (str[i] == little[j] && little[j])
			{
				i++;
				j++;
			}
			if (!little[j])
				return (1);
		}
		i++;
	}
	return (0);
}

void	do_redir(t_minishell *minishell)
{
	if (minishell->redir == R_TRUNC_O)
		redir_trunc_o(minishell);
	else if (minishell->redir == R_APPEND_O)
		redir_append_o(minishell);
	else if (minishell->redir == R_TRUNC_I)
		redir_trunc_in(minishell);
	else if (minishell->redir == R_APPEND_I)
		redir_append_in(minishell);
}
