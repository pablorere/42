/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 21:30:00 by ppaula-s          #+#    #+#             */
/*   Updated: 2026/03/31 21:30:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_all_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			fprintf(stderr, "Warning: Failed to join philosopher %d\n",
				i + 1);
		i++;
	}
	return (1);
}

int	create_philosopher_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				philosopher_routine, &data->philos[i]) != 0)
		{
			fprintf(stderr, "Error: Failed to create thread %d\n", i + 1);
			pthread_mutex_lock(&data->end_mutex);
			data->simulation_end = true;
			data->start_time = get_time();
			pthread_mutex_unlock(&data->end_mutex);
			while (--i >= 0)
				pthread_join(data->philos[i].thread, NULL);
			return (0);
		}
		i++;
	}
	return (1);
}

int	start_monitor_thread(t_data *data, pthread_t *monitor_thread)
{
	if (pthread_create(monitor_thread, NULL, monitor_routine, data) != 0)
	{
		fprintf(stderr, "Error: Failed to create monitor thread\n");
		pthread_mutex_lock(&data->end_mutex);
		data->simulation_end = true;
		pthread_mutex_unlock(&data->end_mutex);
		return (0);
	}
	return (1);
}

int	start_simulation(t_data *data)
{
	pthread_t	monitor_thread;

	if (!create_philosopher_threads(data))
	{
		cleanup_threads(data);
		return (0);
	}
	pthread_mutex_lock(&data->end_mutex);
	data->start_time = get_time();
	pthread_mutex_unlock(&data->end_mutex);
	init_meal_times_inline(data);
	if (!start_monitor_thread(data, &monitor_thread))
	{
		cleanup_threads(data);
		return (0);
	}
	if (pthread_join(monitor_thread, NULL) != 0)
	{
		fprintf(stderr, "Error: Failed to join monitor thread\n");
		return (0);
	}
	return (join_all_philos(data));
}
