/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 23:14:28 by ppaula-s          #+#    #+#             */
/*   Updated: 2026/04/01 05:21:32 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->data->philo_nbr == 1)
		pthread_mutex_lock(philo->left_fork);
	else if (philo->id == philo->data->philo_nbr)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_eat(t_philo *philo)
{
	long	start_ts;
	long	elapsed;
	long	remaining;

	take_forks(philo);
	start_ts = print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = start_ts;
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	elapsed = get_time() - philo->data->start_time - start_ts;
	remaining = philo->data->time_to_eat - elapsed;
	if (remaining > 0)
		ft_usleep(remaining, philo->data);
	drop_forks(philo);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep, philo->data);
}

void	philo_think(t_philo *philo)
{
	print_status(philo, "is thinking");
	ft_usleep(1, philo->data);
}
