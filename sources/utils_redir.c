/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 02:13:12 by waalexan          #+#    #+#             */
/*   Updated: 2024/11/09 16:52:51 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	return_redir_type(char curr_c, char next_c)
{
	if (curr_c == '>' && next_c == '>')
		return (R_APPEND_O);
	else if (curr_c == '<' && next_c == '<')
		return (R_APPEND_I);
	else if (curr_c == '>')
		return (R_TRUNC_O);
	else if (curr_c == '<')
		return (R_TRUNC_I);
	return (0);
}

typedef struct s_utils_redir
{
	int		data_idx;
	int		is_quote;
	int		is_redirect;
	char	*current_arg;
	int		index;
}			t_utils_redir;

int	verify_redir_is_in_qt(char *str, t_utils_redir *vars, int *quote_type)
{
	int	qt_flag;

	qt_flag = vars->is_quote;
	if (str[vars->index] == '"' || str[vars->index] == '\'')
	{
		if (!qt_flag)
		{
			qt_flag = 1;
			*quote_type = (int)str[vars->index];
		}
		else if (str[vars->index] == *quote_type)
			qt_flag = 0;
		vars->is_quote = qt_flag;
		return (1);
	}
	return (0);
}

int	is_redir(char *str)
{
	int				redirect;
	int				quote_type;
	t_utils_redir	vars;

	ft_memset(&vars, 0, sizeof(t_utils_redir));
	while (str[vars.index])
	{
		if (verify_redir_is_in_qt(str, &vars, &quote_type) == 1)
		{
			vars.index++;
			continue ;
		}
		if (!vars.is_quote)
		{
			redirect = return_redir_type(str[vars.index], str[vars.index + 1]);
			if (redirect)
				return (redirect);
		}
		vars.index++;
	}
	return (0);
}

int	check_redir_one(t_minishell *minishell, int i, char *redir_type)
{
	int	len;

	len = ft_strlen(minishell->verify_syntax[i]);
	if (len == 1)
	{
		if (minishell->verify_syntax[i + 1] == NULL)
		{
			redir_syntax_error("SUGAR");
			return (ft_free_matriz(minishell->verify_syntax), 2);
		}
		if ((ft_strncmp(minishell->verify_syntax[i + 1], redir_type, 1) == 0)
			|| ft_strncmp(minishell->verify_syntax[i + 1], "|", 1) == 0)
		{
			redir_syntax_error("PANCAKE");
			return (ft_free_matriz(minishell->verify_syntax), 2);
		}
	}
	return (0);
}

int	check_redir_two(t_minishell *minishell, int i, char *redir_type)
{
	int	len;

	len = ft_strlen(minishell->verify_syntax[i]);
	if (len == 2)
	{
		if (minishell->verify_syntax[i + 1] == NULL)
		{
			redir_syntax_error("SUGAR");
			return (ft_free_matriz(minishell->verify_syntax), 2);
		}
		if ((ft_strncmp(minishell->verify_syntax[i + 1], redir_type, 1) == 0)
			|| ft_strncmp(minishell->verify_syntax[i + 1], "|", 1) == 0)
		{
			redir_syntax_error("PANCAKE");
			return (ft_free_matriz(minishell->verify_syntax), 2);
		}
	}
	return (0);
}
