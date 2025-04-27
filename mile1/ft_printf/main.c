/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:34:54 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/04/27 18:34:54 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int main(void)
{
	int len1, len2;
	int n = 42;
	char c = 'A';
	char *str = "Hello, world!";
	void *ptr = &n;
	unsigned int u = 4294967295U;
	int d =  -2147483649;
	int i = 6789;
	unsigned int x = 0xdeadbeef;

	// %%
	len1 = ft_printf("ft_printf: %%\n");
	len2 = printf("printf   : %%\n");
	printf("ft_printf returned: %d | printf returned: %d\n\n", len1, len2);

	// %c
	len1 = ft_printf("ft_printf: %c\n", c);
	len2 = printf("printf   : %c\n", c);
	printf("ft_printf returned: %d | printf returned: %d\n\n", len1, len2);

	// %s
	len1 = ft_printf("ft_printf: %s\n", str);
	len2 = printf("printf   : %s\n", str);
	printf("ft_printf returned: %d | printf returned: %d\n\n", len1, len2);

	// %p
	len1 = ft_printf("ft_printf: %p\n", ptr);
	len2 = printf("printf   : %p\n", ptr);
	printf("ft_printf returned: %d | printf returned: %d\n\n", len1, len2);

	// %d
	len1 = ft_printf("ft_printf: %d\n", d);
	len2 = printf("printf   : %d\n", d);
	printf("ft_printf returned: %d | printf returned: %d\n\n", len1, len2);

	// %i
	len1 = ft_printf("ft_printf: %i\n", i);
	len2 = printf("printf   : %i\n", i);
	printf("ft_printf returned: %d | printf returned: %d\n\n", len1, len2);

	// %u
	len1 = ft_printf("ft_printf: %u\n", u);
	len2 = printf("printf   : %u\n", u);
	printf("ft_printf returned: %d | printf returned: %d\n\n", len1, len2);

	// %x
	len1 = ft_printf("ft_printf: %x\n", x);
	len2 = printf("printf   : %x\n", x);
	printf("ft_printf returned: %d | printf returned: %d\n\n", len1, len2);

	// %X
	len1 = ft_printf("ft_printf: %X\n", x);
	len2 = printf("printf   : %X\n", x);
	printf("ft_printf returned: %d | printf returned: %d\n\n", len1, len2);

	return 0;
}