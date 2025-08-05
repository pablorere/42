/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42urduliz.com   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 04:34:14 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/08/04 04:34:14 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		ft_errors("Error: Invalid arguments\n"
			GREEN"Usage: ./philo 5 800 200 200 [5]\n"RESET);
		return (1);
	}
	parse(&table, av);
	init_sim(&table);
	start_sim(&table);
	clean(&table);
	return (0);
}
