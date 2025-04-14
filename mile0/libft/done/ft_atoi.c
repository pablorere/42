/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:09:20 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/04/14 17:49:19 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>
#include <stdlib.h> 
#include "libft.h"

int	ft_isspace(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	n;

	i = 0;
	n = 0;
	while (ft_isspace(nptr[i]))
		i++;
	sign = 1 - 2 * (nptr[i] == '-');
	i += nptr[i] == '+' || nptr[i] == '-';
	while (ft_isdigit(nptr[i]))
		n = n * 10 + (nptr[i++] - '0');
	return (n * sign);
}
int	main(int ac, char **av)
{
	printf("la originalllll: %d\n", atoi(av[1]));
	printf("la mia: %d\n", ft_atoi(av[1]));
}
