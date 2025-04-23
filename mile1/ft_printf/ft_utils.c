/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 08:00:04 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/04/23 08:00:04 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	return (write(1, str, ft_strlen(str)));
}

int	ft_putnb(long n, int base, int boo, int len)
{
	if (boo == 3 && len == 0)
	{
		len += 2;
		ft_putstr("0x");
	}
	if (n < 0)
	{
		len += write(1, "-", 1);
		n = -n;
	}
	if (n >= base)
		len += ft_putnb(n / base, base, boo, len);
	if (boo == 1)
		len += ft_putchar(UPBASE[n % base]);
	else if (boo == 0)
		len += ft_putchar(LOWBASE[n % base]);
	return (len);
	len += ft_putchar(LOWBASE[n % base]);
	return (len);
}
