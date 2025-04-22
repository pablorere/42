/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:54:48 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/04/22 18:35:16 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#define hex "0123456789abcdef"
#define HEX "0123456789ABCDEF"

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void print_hex(unsigned int num, char *dic)
{
	if (num >= 16)
		print_hex(num / 16, dic);
	ft_putchar(dic[num % 16]);
}

int main(void)
{
	unsigned int num;

	num = 0x013984;
	print_hex(num, HEX);
	ft_putchar('\n');
	return (0);
}
