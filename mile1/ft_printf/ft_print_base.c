/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:51:12 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/04/22 21:49:48 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include "libft.h"

#define hex "0123456789abcdef"
#define HEX "0123456789ABCDEF"

size_t	ft_strlen(const char *s);

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void ft_print_base(unsigned int num, int base, int i)
{
	if (num >= base)
		ft_print_base(num / base, base);
	ft_putchar(base[num % base]);
}

/*int main(void)
{
	unsigned int num;

	printf("hexadecimal: %zu\n", sizeof(hex));
	num = 16;
	ft_print_base(num, HEX);
	ft_putchar('\n');
	return (0);
}*/
