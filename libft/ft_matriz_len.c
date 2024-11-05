/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matriz_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:15:16 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/05 00:21:26 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_matriz_len(char **matriz)
{
	int	i;

	i = 0;
	while (matriz[i])
		i++;
	return (i);
}

int	ft_matriz_len2(char matriz[MAX_WORDS][MAX_WORD_LENGTH])
{
	int	i;

	i = 0;
	while (matriz[i][0])
		i++;
	return (i);
}
