/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 06:39:24 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/04/09 07:33:15 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *out, const char *in, size_t outsize)
{
	size_t	insize;
	size_t	i;

	if (!out || !in)
		return (0);
	insize = ft_strlen(in);
	i = 0;
	if (outsize != 0)
	{
		while (in[i] != '\0' && i < (outsize - 1))
		{
			out[i] = in[i];
			i++;
		}
		out[i] = '\0';
	}
	return (insize);
}
