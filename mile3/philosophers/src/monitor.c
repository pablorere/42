/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 23:14:35 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/12/20 18:46:01 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	announce_death(t_data *data, int philo_id, long death_time)
{
	pthread_mutex_lock(&data->print_mutex);
	printf("%ld %d died\n", death_time - data->start_time, philo_id);
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_lock(&data->end_mutex);
	data->simulation_end = true;
	pthread_mutex_unlock(&data->end_mutex);
}

static bool	is_philosopher_dead(t_data *data, int i, long current_time)
{
	long	last_meal;
	bool	is_dead;

	pthread_mutex_lock(&data->meal_mutex);
	last_meal = data->philos[i].last_meal_time;
	is_dead = (current_time - last_meal >= data->time_to_die);
	pthread_mutex_unlock(&data->meal_mutex);
	return (is_dead);
}

bool	check_death(t_data *data)
{
	int		i;
	long	current_time;

	i = 0;
	while (i < data->philo_nbr)
	{
		current_time = get_time();
		if (is_philosopher_dead(data, i, current_time))
		{
			announce_death(data, data->philos[i].id, current_time);
			return (true);
		}
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
		usleep(500);
	}
	return (NULL);
}