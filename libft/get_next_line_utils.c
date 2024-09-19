/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:24:30 by gkomba            #+#    #+#             */
/*   Updated: 2024/05/25 16:37:13 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_buffer(int fd, char *chr, int *buffer_size, int *buffer_pos)
{
	*buffer_size = read(fd, chr, BUFFER_SIZE);
	*buffer_pos = 0;
	return (*buffer_size);
}

int	ft_get_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_string_dup(char *src)
{
	char	*dest;
	int		i;
	int		len;

	i = 0;
	len = ft_get_len(src);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (0);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	s_v_i(int *vars)
{
	if (vars[2] == 0)
	{
		vars[0] = 0;
		vars[1] = 0;
		vars[2] = 1;
	}
}
