/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matriz.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:03:37 by gkomba            #+#    #+#             */
/*   Updated: 2024/10/29 16:23:06 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*free_ptr(char *ptr)
{
	free(ptr);
	ptr = NULL;
	return (NULL);
}

char	**ft_free_matriz(char **mat)
{
	size_t	i;

	i = -1;
	while (mat[++i])
		mat[i] = free_ptr(mat[i]);
	free (mat);
	mat = NULL;
	return (NULL);
}
