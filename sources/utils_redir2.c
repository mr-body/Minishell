/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:45:45 by gkomba            #+#    #+#             */
/*   Updated: 2024/12/14 22:24:23 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	verif_redir_two(t_minishell *minishell)
{
	int	redir;
	int	retrn;

	redir = 0;
	if (minishell->args)
		free_data(minishell->args);
	if (extract_command(minishell, &redir, &retrn) != 0)
		exit(1);
	if (redir == R_TRUNC_O)
		redir_trunc_o(minishell, 0, 0);
	else if (redir == R_APPEND_O)
		redir_append_o(minishell, 0, 0);
	else if (redir == R_TRUNC_I)
		redir_trunc_in(minishell, 0, 0);
	else if (redir == R_APPEND_I)
		redir_append_in(minishell, 0);
	if (!minishell->args || minishell->not_flag == -1)
	{
		minishell->not_flag = 0;
		return (1);
	}
	return (0);
}

int	redir_alone(t_minishell *minishell, int i, char *redir_type)
{
	int	j;

	j = 0;
	while (minishell->verify_syntax[i][j])
	{
		if ((minishell->verify_syntax[i][j] == redir_type[0])
			&& (minishell->verify_syntax[i][j + 1] == '\0')
			&& (minishell->verify_syntax[i] == NULL))
		{
			redir_syntax_error("SUGAR");
			return (ft_free_matriz(minishell->verify_syntax), 2);
		}
		j++;
	}
	return (0);
}

int	redir_alone_two(t_minishell *minishell, int i, char *redir_type)
{
	int	j;

	j = 0;
	while (minishell->verify_syntax[i][j])
	{
		if ((minishell->verify_syntax[i][j] == redir_type[0])
			&& (minishell->verify_syntax[i][j + 1] == redir_type[1])
			&& (minishell->verify_syntax[i][j + 2] == '\0')
			&& (minishell->verify_syntax[i + 1] == NULL))
		{
			redir_syntax_error("SUGAR");
			return (ft_free_matriz(minishell->verify_syntax), 2);
		}
		j++;
	}
	return (0);
}
