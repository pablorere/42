/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silvertape <silvertape@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:12:51 by silvertape        #+#    #+#             */
/*   Updated: 2025/06/18 19:07:36 by silvertape       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#define ISSPACE ((c >= 9 && c <= 13 || c == 32))
#define c (av[1][i])
int ft_strlen(char * str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
int ft_putstr(char *str)
{
		write(1, str, ft_strlen(str));
	return (0);
}
int main(int ac, char **av)
{
	
	if(ac == 1 || ac == 2)
		ft_putstr("not enough arguments\n");
		if isspace
	return (0);
}