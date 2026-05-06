/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silvertape <silvertape@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:09:20 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/05/23 15:50:09 by silvertape       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#define space (str[i] == 32 || (str[i] >= 9 &&str[i] <= 13))

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	n;

	i = 0;
	n = 0;
	while (space)
		i++;
	sign = 1 - 2 * (str[i] == '-');
	i +=str[i] == '+' ||str[i] == '-';
	while (ft_isdigit(str[i]))
		n = n * 10 + (str[i++] - '0');
	return (n * sign);
}

#include <stdio.h>

int	main(void)
{
	printf("la originalllll: %d\n", atoi("   -1234"));
	printf("la mia: %d\n", ft_atoi("   -1234"));
}

