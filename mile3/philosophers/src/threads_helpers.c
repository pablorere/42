/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 21:30:00 by ppaula-s          #+#    #+#             */
/*   Updated: 2026/03/31 21:30:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
		pthread_join(data->philos[i++].thread, NULL);
}

void	init_meal_times_inline(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_mutex_lock(&data->meal_mutex);
		data->philos[i].last_meal_time = get_time() - data->start_time;
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
}
