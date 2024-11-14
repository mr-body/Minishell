/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:30:29 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/13 10:59:25 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redir_trunc_o_aux(t_minishell *minishell)
{
	char	**redir_matrix;
	char	**redir_matrix2;

	redir_matrix = ft_split_ms(minishell->redirect_command, '>');
	if (ft_matriz_len(redir_matrix) == 1)
	{
		redir_matrix2 = ft_split_ms(redir_matrix[0], ' ');
		if (ft_matriz_len(redir_matrix2) == 1)
		{
			ft_free_matriz(redir_matrix);
			ft_free_matriz(redir_matrix2);
			redir_trunc_o_case_one(minishell);
			return (1);
		}
		ft_free_matriz(redir_matrix2);
	}
	ft_free_matriz(redir_matrix);
	return (0);
}

int	redir_append_o_aux(t_minishell *minishell)
{
	char	**redir_matrix;
	char	**redir_matrix2;

	redir_matrix = ft_split_ms(minishell->redirect_command, '>');
	if (ft_matriz_len(redir_matrix) == 1)
	{
		redir_matrix2 = ft_split_ms(redir_matrix[0], ' ');
		if (ft_matriz_len(redir_matrix2) == 1)
		{
			ft_free_matriz(redir_matrix);
			ft_free_matriz(redir_matrix2);
			redir_append_o_case_one(minishell);
			return (1);
		}
		ft_free_matriz(redir_matrix2);
	}
	ft_free_matriz(redir_matrix);
	return (0);
}

int	redir_trunc_in_aux(t_minishell *minishell)
{
	char	**redir_matrix;
	char	**redir_matrix2;

	redir_matrix = ft_split_ms(minishell->redirect_command, '<');
	if (ft_matriz_len(redir_matrix) == 1)
	{
		redir_matrix2 = ft_split_ms(redir_matrix[0], ' ');
		if (ft_matriz_len(redir_matrix2) == 1)
		{
			ft_free_matriz(redir_matrix);
			ft_free_matriz(redir_matrix2);
			redir_trunc_in_case_one(minishell);
			return (1);
		}
		ft_free_matriz(redir_matrix2);
	}
	ft_free_matriz(redir_matrix);
	return (0);
}

int	redir_append_in_aux(t_minishell *minishell, t_redirect *var)
{
	char	**redir_matrix;
	char	**redir_matrix2;

	redir_matrix = ft_split_ms(minishell->redirect_command, '<');
	if (ft_matriz_len(redir_matrix) == 1)
	{
		redir_matrix2 = ft_split_ms(redir_matrix[0], ' ');
		if (ft_matriz_len(redir_matrix2) == 1)
		{
			ft_free_matriz(redir_matrix);
			ft_free_matriz(redir_matrix2);
			redir_append_in_case_one(minishell, var);
			return (1);
		}
		ft_free_matriz(redir_matrix2);
	}
	ft_free_matriz(redir_matrix);
	return (0);
}