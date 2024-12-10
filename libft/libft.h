/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:04:29 by gkomba            #+#    #+#             */
/*   Updated: 2024/12/10 10:25:49 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "get_next_line.h"
# include "limits.h"
# include <stdlib.h>
# include <unistd.h>

# define MAX_WORDS 1024
# define MAX_WORD_LENGTH 1024
# define MAX_ARGS 1024

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_isspace(int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t len);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_count_chr_occurrency_matriz(char **mat, char chr);
int		ft_count_chr_occurrency_str(char *str, char chr);
int		ft_strncmp2(const char *s1, const char *s2, size_t n);
int		ft_matriz_len2(char matriz[MAX_WORDS][MAX_WORD_LENGTH]);
int		ft_matriz_len3(char *data2[MAX_ARGS]);
int		ft_atoi(const char *nptr);
int		ft_atoi_v2(const char *nptr);
size_t	ft_strlen(const char *str);
int		ft_strnlen(const char *s, char n);
int		ft_matriz_len(char **matriz);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_print_matriz(char **matriz);
void	ft_delete_chr_on_str(char *str, char chr);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	ft_strtok(char *str, char *delimiter,
			char result[MAX_WORDS][MAX_WORD_LENGTH]);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_strcat(char *s1, char *s2, int c);
char	*ft_strcat_no_malloc(char *dest, char *src);
char	**ft_split(const char *s, char c);
char	*ft_itoa(int n);
char	*ft_strnstr(const char *big, const char *little, size_t n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strrchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_free_matriz(char **mat);
char	**ft_matdup(char **mat);
char	*ft_mattstr_copy(char **mat);
char	*free_ptr(char *ptr);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strncpy(char *dest, const char *src, unsigned int n);
char	*ft_strncat(char *dest, char *src, unsigned int nb);
char	**free_split(char **split, size_t word);
char	**ft_free_matriz2(char *matriz[MAX_ARGS]);
char	*ft_strndup(const char *str, int n);

#endif
