/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:02:26 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/08 12:48:56 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while ((char)c != *s)
	{
		if (!*s)
			return (0);
		s++;
	}
	return ((char *)s);
}

int	ft_strchr_quote(const char *str, char c)
{
	int	in_quotes;

	if (str == NULL)
		return (1);
	in_quotes = 0;
	while (*str)
	{
		if (*str == '"' || *str == '\'')
			in_quotes = !in_quotes;
		if (*str == c)
		{
			if (in_quotes)
				return (1);
			return (0);
		}
		str++;
	}
	return (1);
}
