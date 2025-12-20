/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 23:14:28 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/12/20 18:58:30 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		if (!check_simulation_end(philo->data))
			print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		if (!check_simulation_end(philo->data))
			print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		if (!check_simulation_end(philo->data))
			print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		if (!check_simulation_end(philo->data))
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
	take_forks(philo);
	if (!check_simulation_end(philo->data))
	{
		pthread_mutex_lock(&philo->data->meal_mutex);
		philo->last_meal_time = get_time();
		pthread_mutex_unlock(&philo->data->meal_mutex);
		print_status(philo, "is eating");
		pthread_mutex_lock(&philo->data->meal_mutex);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->data->meal_mutex);
		ft_usleep(philo->data->time_to_eat, philo->data);
	}
	drop_forks(philo);
}

void	philo_sleep(t_philo *philo)
{
	if (!check_simulation_end(philo->data))
	{
		print_status(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep, philo->data);
	}
}

void	philo_think(t_philo *philo)
{
	long	time_to_think;

	if (!check_simulation_end(philo->data))
		print_status(philo, "is thinking");
	if (philo->data->philo_nbr % 2 != 0)
	{
		time_to_think = (philo->data->time_to_eat * 2)
			- philo->data->time_to_sleep;
		if (time_to_think < 0)
			time_to_think = 0;
		if (time_to_think > 600)
			time_to_think = 600;
		if (time_to_think > 0)
			ft_usleep(time_to_think, philo->data);
	}
}
