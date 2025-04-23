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
	write(1, str, ft_strlen(str));
}

int	ft_putnb(long n, int base, int boo, int len)
{
	int	flag;

	if (boo == 3 && flag == NULL)
	{
		len += 2;
		ft_putstr("0x");
		flag = 1;
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
/*
int	main(int ac, char *av[])
{
	int	number;

	number = ft_atoi(av[1]);
	if (ac < 2)
	{
		write(1, "Usage: ./a.out <number>\n", 24);
		return (1);
	}
	ft_putnb((long)number, 16, 0, 0);
	write(1, "\n", 1);
	printf("%x \n", number);
	return (0);
}
*/