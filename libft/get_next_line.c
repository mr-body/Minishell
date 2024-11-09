/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:29:49 by gkomba            #+#    #+#             */
/*   Updated: 2024/05/25 16:51:05 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	chr[BUFFER_SIZE];
	char		str[7000000];
	static int	vars[3];
	int			i;

	s_v_i(vars);
	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (vars[0] >= vars[1])
			if (read_buffer(fd, chr, &vars[1], &vars[0]) <= 0)
				break ;
		str[i++] = chr[vars[0]++];
		if (str[i - 1] == '\n')
			break ;
	}
	str[i] = '\0';
	if (i == 0)
		return (NULL);
	return (ft_string_dup(str));
}
