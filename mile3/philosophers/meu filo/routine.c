/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silvertape <silvertape@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 23:14:28 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/10/26 16:05:42 by silvertape       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->data->philo_nbr == 1)
		return ;
	if (philo->id % 2 == 0)
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
	if (philo->data->philo_nbr == 1)
		return ;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_eat(t_philo *philo)
{
	if (philo->data->philo_nbr == 1)
	{
		print_status(philo, "has taken a fork");
		ft_usleep(philo->data->time_to_die, philo->data);
		return ;
	}
	take_forks(philo);
	if (check_simulation_end(philo->data))
	{
		drop_forks(philo);
		return ;
	}
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	print_status(philo, "is eating");
	ft_usleep(philo->data->time_to_eat, philo->data);
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
}
