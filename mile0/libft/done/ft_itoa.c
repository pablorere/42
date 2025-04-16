/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:03:01 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/04/16 12:16:36 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	unsigned int	cpy;
	int				i;
	char			*str;

	i = (n < 0);
	cpy = n;
	while (cpy != 0)
	{
		i ++;
		cpy /= 10;
	}
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '-';
	str[i] = '\0';
	cpy = n;
	if (n < 0)
		cpy = -n;
	while (cpy)
	{
		str[--i] = '0' + (cpy % 10);
		cpy /= 10;
	}
	return (str);
}
/*
int main(int argc, char const *argv[])
{
	char *str = ft_itoa(0);
	printf("Numero: %s\n", str);
	if (str)
		free(str);
	return 0;
}*/