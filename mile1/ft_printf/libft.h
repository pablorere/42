/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:22:44 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/04/19 18:27:24 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>

int		ft_isalpha(int c);

int		ft_isascii(int c);

int		ft_isalnum(int c);

int		ft_isdigit(int c);

int		ft_isprint(int c);

int		ft_atoi(const char *nptr);

int		ft_toupper(int c);

int		ft_tolower(int c);

void	*ft_memset(void *s, int c, size_t n);

void	ft_bzero(void *s, size_t n);

void	*ft_calloc(size_t nmemb, size_t size);

int		ft_memcmp(const void *s1, const void *s2, size_t n);

void	*ft_memcpy(void *dest, const void *src, size_t n);

void	*ft_memmove(void *dest, const void *src, size_t n);

void	*ft_memchr(const void *s, int c, size_t n);

int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*strrchr(const char *s, int c);

char	*ft_strchr(const char *s, int c);

char	*ft_strdup(const char *s);

size_t	ft_strlcpy(char *dst, const char *src, size_t size);

size_t	ft_strlen(const char *s);

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

void	ft_putchar_fd(char c, int fd);

void	ft_putnbr_fd(int n, int fd);

void	ft_putstr_fd(char *s, int fd);

char	*ft_strtrim(char const *s1, char const *set);

void	ft_putendl_fd(char *s, int fd);

char	*ft_itoa(int n);

char	*ft_strnstr(const char *big, const char *little, size_t len);

char	*ft_substr(const char *s, unsigned int start, size_t len);

#endif
