/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:12:22 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/07 18:14:16 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, char *s2, int c)
{
	size_t	len1;
	size_t	len2;
	char	*new;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new = malloc(len1 + len2 + 2);
	if (!new)
		return (NULL);
	ft_memcpy(new, s1, len1);
	new[len1] = (char)c;
	ft_memcpy(new + len1 + 1, s2, len2);
	new[len1 + len2 + 1] = '\0';
	return (new);
}

char	*ft_strcat_no_malloc(char *dest, char *src)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (dest[j] != '\0')
	{
		j++;
	}
	while (src[i] != '\0')
	{
		dest[j + i] = src[i];
		i++;
	}
	dest[j + i] = '\0';
	return (dest);
}
