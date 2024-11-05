/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:35:50 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/05 16:06:35 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verify_pipes_syntax(t_minishell *minishell)
{
	int	i;

	i = 0;
	minishell->verify_pipes_syntax = ft_split_ms(minishell->command, '|');
	while (minishell->verify_pipes_syntax[i])
	{
		if (ft_is_only(minishell->verify_pipes_syntax[i], ' '))
		{
			ft_putendl_fd("bash: syntax error near unexpected token `|'", 2);
			ft_free_matriz(minishell->verify_pipes_syntax);
			return (2);
		}
		i++;
	}
	ft_free_matriz(minishell->verify_pipes_syntax);
	return (0);
}