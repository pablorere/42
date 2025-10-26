/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 23:15:22 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/10/22 23:36:26 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long ms)
{
	long	start;

	start = get_time();
	while (get_time() - start < ms)
		usleep(100);
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->data->end_mutex);
	if (!philo->data->simulation_end)
	{
		pthread_mutex_unlock(&philo->data->end_mutex);
		pthread_mutex_lock(&philo->data->print_mutex);
		pthread_mutex_lock(&philo->data->end_mutex);
		if (!philo->data->simulation_end)
			printf("%ld %d %s\n", get_time() - philo->data->start_time,
				philo->id, status);
		pthread_mutex_unlock(&philo->data->end_mutex);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	else
		pthread_mutex_unlock(&philo->data->end_mutex);
}

void	ft_error(char *msg)
{
	printf("%s", msg);
	exit(1);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		res = res * 10 + (*str++ - '0');
	return (res * sign);
}
