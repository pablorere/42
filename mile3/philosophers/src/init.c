/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:21:27 by ppaula-s          #+#    #+#             */
/*   Updated: 2026/03/31 21:37:20 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_nbr);
	if (!data->forks)
		return (0);
	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			free(data->forks);
			data->forks = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_philosophers(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->philo_nbr);
	if (!data->philos)
		return (0);
	i = 0;
	while (i < data->philo_nbr)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->philo_nbr];
		data->philos[i].data = data;
		i++;
	}
	return (1);
}

static void	cleanup_init_on_error(t_data *data, int philo_init_failed)
{
	int	i;

	if (philo_init_failed)
	{
		i = 0;
		while (i < data->philo_nbr)
			pthread_mutex_destroy(&data->forks[i++]);
		free(data->forks);
		free(data->philos);
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->end_mutex);
}

int	init_simulation(t_data *data)
{
	data->simulation_end = false;
	data->start_time = 0;
	if (!init_mutexes(data))
		return (0);
	if (!init_forks(data))
	{
		cleanup_init_on_error(data, 0);
		return (0);
	}
	if (!init_philosophers(data))
	{
		cleanup_init_on_error(data, 1);
		return (0);
	}
	return (1);
}

void	cleanup_simulation(t_data *data)
{
	int	i;

	if (!data)
		return ;
	if (data->forks)
	{
		i = 0;
		while (i < data->philo_nbr)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
		data->forks = NULL;
	}
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->end_mutex);
}
