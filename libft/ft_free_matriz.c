/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matriz.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:03:37 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/07 19:12:08 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*free_ptr(char *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
	return (NULL);
}

char	**ft_free_matriz(char **mat)
{
	size_t	i;

	i = -1;
	while (mat && mat[++i])
		mat[i] = free_ptr(mat[i]);
	free (mat);
	mat = NULL;
	return (NULL);
}

char	**ft_free_matriz2(char *matriz[MAX_ARGS])
{
	int	i;

	i = 0;
	while (matriz[i] != NULL && matriz[i][0] != '\0')
	{
		matriz[i] = free_ptr(matriz[i]);
		i++;
	}
	return (NULL);
}
