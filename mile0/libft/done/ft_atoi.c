/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:09:20 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/04/13 18:11:06 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>
#include <stdlib.h> 

int ft_isdigit(int num)
{
	return (num >= '0' && num <= '9');
}

int	ft_atoi(const char *nptr)
{
	int				i;
	int				sign;
	unsigned int	n;

	i = 0;
	n = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	sign = 1 - 2 * (nptr[i] == '-');
	i += nptr[i] == '+' || nptr[i] == '-';
	while (ft_isdigit(nptr[i]))
	{
		if (n > INT_MAX / 10
			|| (n == INT_MAX / 10 && (nptr[i] - '0') > INT_MAX % 10))
			return (-(sign == 1));
		n = n * 10 + (nptr[i++] - '0');
	}
	return ((int)(n * sign));
}
int	main(int ac, char **av)
{
	printf("la originalllll: %d\n", atoi(av[1]));
	printf("la mia: %d\n", ft_atoi(av[1]));
}
