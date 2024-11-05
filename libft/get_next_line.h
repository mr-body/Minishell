/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <<marvin@42.fr> >                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:29:34 by gkomba            #+#    #+#             */
/*   Updated: 2024/08/13 12:53:20 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

char	*ft_string_dup(char *src);
char	*get_next_line(int fd);
void	s_v_i(int *vars);
int		read_buffer(int fd, char *chr, int *buffer_size, int *buffer_pos);
int		ft_get_len(char *str);

#endif
