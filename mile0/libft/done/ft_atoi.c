/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:09:20 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/04/14 15:09:26 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>
#include <stdlib.h> 
<<<<<<< HEAD
#include "libft.h"
=======
>>>>>>> refs/remotes/origin/main

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
<<<<<<< HEAD
=======
	{
		if (n > INT_MAX / 10
			|| (n == INT_MAX / 10 && (nptr[i] - '0') > INT_MAX % 10))
			return (-(sign == 1));
>>>>>>> refs/remotes/origin/main
		n = n * 10 + (nptr[i++] - '0');
	return (n * sign);
}
int	main(int ac, char **av)
{
	printf("la originalllll: %d\n", atoi(av[1]));
	printf("la mia: %d\n", ft_atoi(av[1]));
}
