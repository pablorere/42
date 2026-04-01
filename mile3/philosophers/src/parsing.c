/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 21:30:00 by ppaula-s          #+#    #+#             */
/*   Updated: 2026/03/31 21:30:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parse_args(t_data *data, char **av)
{
	data->philo_nbr = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (data->philo_nbr <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		ft_error("Error: All arguments must be positive integers\n");
	if (av[5])
	{
		data->limit_meals = ft_atoi(av[5]);
		if (data->limit_meals <= 0)
			ft_error("Error: nbr_meals must be a positive integer\n");
	}
	else
		data->limit_meals = -1;
}
