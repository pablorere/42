/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:00:00 by ppaula-s          #+#    #+#             */
/*   Updated: 2026/04/01 05:23:38 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
	{
		ft_error("Error: Invalid arguments\n"
			"Usage: ./philo N ttdie tteat ttsleep [n_meals]\n");
		return (1);
	}
	parse_args(&data, av);
	if (!init_simulation(&data))
	{
		fprintf(stderr, "Error: Failed to initialize simulation\n");
		return (1);
	}
	if (!start_simulation(&data))
	{
		fprintf(stderr, "Error: Failed to start simulation\n");
		cleanup_simulation(&data);
		return (1);
	}
	cleanup_simulation(&data);
	return (0);
}

static void	philo_wait_for_start(t_philo *philo)
{
	while (true)
	{
		pthread_mutex_lock(&philo->data->end_mutex);
		if (philo->data->start_time != 0)
		{
			pthread_mutex_unlock(&philo->data->end_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->end_mutex);
		usleep(100);
	}
}

static void	philo_one_routine(t_philo *philo)
{
	print_status(philo, "has taken a fork");
	while (!check_simulation_end(philo->data))
		usleep(1000);
}

void	*philosopher_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	philo_wait_for_start(philo);
	if (philo->data->philo_nbr == 1)
	{
		philo_one_routine(philo);
		return (NULL);
	}
	while (!check_simulation_end(philo->data))
	{
		philo_eat(philo);
		philo_think(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

bool	check_simulation_end(t_data *data)
{
	bool	end;

	pthread_mutex_lock(&data->end_mutex);
	end = data->simulation_end;
	pthread_mutex_unlock(&data->end_mutex);
	return (end);
}
