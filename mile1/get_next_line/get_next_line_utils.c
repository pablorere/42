/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 00:22:09 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/04/28 00:22:09 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	const unsigned char	*src2;
	unsigned char		*dest2;

	if (!dest && !src)
		return (NULL);
	i = 0;
	src2 = src;
	dest2 = dest;
	while (i < n)
	{
		dest2[i] = src2[i];
		i++;
	}
	return (dest);
}

size_t	ft_strlen(const char *n)
{
	size_t	i;

	if (!n)
		return (0);
	i = 0;
	while (n[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*res;

	if (!s1 && !s2)
	{
		res = malloc(1);
		if (res)
			res[0] = '\0';
		return (res);
	}
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = (char *)malloc(len1 + len2 + 1);
	if (!res)
		return (NULL);
	if (s1)
		ft_strlcpy(res, s1, len1 + 1);
	else
		res[0] = '\0';
	if (s2)
		ft_strlcpy(res + len1, s2, len2 + 1);
	else
		res[len1] = '\0';
	return (res);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t outsize)
{
	size_t	srcsize;
	size_t	i;

	if (!src)
	{
		if (outsize != 0 && dst)
			dst[0] = '\0';
		return (0);
	}
	srcsize = ft_strlen(src);
	i = 0;
	if (outsize != 0)
	{
		while (src[i] != '\0' && i < (outsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srcsize);
}

int	ft_findnewline(const char *s)
{
	int	a;

	a = 0;
	while (s[a] != '\0')
	{
		if (s[a] == '\n')
			return (a);
		a++;
	}
	return (-1);
}
