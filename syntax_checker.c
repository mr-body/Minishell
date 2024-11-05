/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:35:50 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/05 15:57:09 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
<<<<<<< HEAD

int	verify_pipes_syntax(char **matrix)
{
	int	i;

	i = 0;
	minishell->verify_pipes_syntax = ft_split_ms(minishell->command, '|');
	while (matrix[i])
	{
		if (ft_is_only(matrix[i], ' '))
		{
			ft_putendl_fd("bash: syntax error near unexpected token `|'", 2);
			ft_free_matrix(minishell->verify_pipes_syntax);
			return (2);
		}
		i++;
	}
	ft_free_matrix(minishell->verify_pipes_syntax);
	return (0);
}