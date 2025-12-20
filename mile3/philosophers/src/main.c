/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:00:00 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/11/18 16:23:58 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
	{
		ft_error("Error: Invalid arguments\nUsage: \
			./philo 5 800 200 200 [5]\n");
		return (1);
	}
	parse_arguments(&data, av);
	init_simulation(&data);
	start_simulation(&data);
	cleanup_simulation(&data);
	return (0);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->philo_nbr == 1)
	{
		print_status(philo, "has taken a fork");
		while (!check_simulation_end(philo->data))
			usleep(1000);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(1, philo->data);
	while (!check_simulation_end(philo->data))
	{
		philo_think(philo);
		philo_eat(philo);
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
