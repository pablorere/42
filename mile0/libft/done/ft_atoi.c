/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:11:07 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/04/08 21:03:25 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	total;
	int	i;
	int	sign;

	sign = 1;
	total = 0;
	i = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\f'
		|| nptr[i] == '\r' || nptr[i] == '\n' || nptr[i] == '\v')
		i++;
	if (nptr[i] == 43 || nptr[i] == 45 || nptr[i] == 32)
	{
		if (nptr[i] == 45)
			sign = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		total = total * 10 + (nptr[i] - 48);
		i++;
	}
	return (total * sign);
}
