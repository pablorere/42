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

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int				i;
	int				sign;
	unsigned int	n;

	i = 0;
	sign = 1;
	n = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		if (n > INT_MAX / 10
			|| (n == INT_MAX / 10 && (nptr[i] - '0') > INT_MAX % 10))
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
		n = n * 10 + (nptr[i++] - '0');
	}
	return ((int)(n * sign));
}
