/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_matriz.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 00:24:19 by waalexan          #+#    #+#             */
/*   Updated: 2024/11/05 00:24:32 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_matriz(char **matriz)
{
	int	i;

	i = -1;
	while (matriz[++i])
	{
		ft_putstr_fd("[", 1);
		ft_putnbr_fd(i, 1);
		ft_putstr_fd("] ", 2);
		ft_putendl_fd(matriz[i], 1);
	}
}
