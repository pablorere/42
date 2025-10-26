/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 23:14:35 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/10/22 23:34:19 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_death(t_data *data)
{
	int		i;
	long	current_time;

	i = 0;
	while (i < data->philo_nbr)
	{
		current_time = get_time();
		pthread_mutex_lock(&data->meal_mutex);
		if (current_time - data->philos[i].last_meal_time > data->time_to_die)
		{
			pthread_mutex_unlock(&data->meal_mutex);
			pthread_mutex_lock(&data->print_mutex);
			printf("%ld %d died\n", get_time() - data->start_time,
				data->philos[i].id);
			pthread_mutex_unlock(&data->print_mutex);
			pthread_mutex_lock(&data->end_mutex);
			data->simulation_end = true;
			pthread_mutex_unlock(&data->end_mutex);
			return (true);
		}
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	return (false);
}

bool	check_all_ate(t_data *data)
{
	int	i;
	int	full_count;

	if (data->limit_meals == -1)
		return (false);
	full_count = 0;
	pthread_mutex_lock(&data->meal_mutex);
	i = 0;
	while (i < data->philo_nbr)
	{
		if (data->philos[i].meals_eaten >= data->limit_meals)
			full_count++;
		i++;
	}
	pthread_mutex_unlock(&data->meal_mutex);
	if (full_count == data->philo_nbr)
	{
		pthread_mutex_lock(&data->end_mutex);
		data->simulation_end = true;
		pthread_mutex_unlock(&data->end_mutex);
		return (true);
	}
	return (false);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!check_simulation_end(data))
	{
		if (check_death(data) || check_all_ate(data))
			break ;
		usleep(1000);
	}
	return (NULL);
}

void	start_simulation(t_data *data)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_create(&data->philos[i].thread, NULL,
			philosopher_routine, &data->philos[i]);
		i++;
	}
	pthread_create(&monitor_thread, NULL, monitor_routine, data);
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}
