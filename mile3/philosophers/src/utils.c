/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:37:29 by ppaula-s          #+#    #+#             */
/*   Updated: 2026/03/31 21:27:51 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long ms, t_data *data)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < ms)
	{
		if (check_simulation_end(data))
			break ;
		usleep(50);
	}
}

void	print_status(t_philo *philo, char *status)
{
	long	timestamp;

	timestamp = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->end_mutex);
	if (philo->data->simulation_end)
	{
		pthread_mutex_unlock(&philo->data->end_mutex);
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->end_mutex);
	printf("%ld %d %s\n", timestamp, philo->id, status);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	ft_error(char *msg)
{
	printf("%s", msg);
	exit(1);
}

int	ft_atoi(const char *str)
{
	long	res;
	int		sign;

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
	{
		res = res * 10 + (*str++ - '0');
		if (res > INT_MAX && sign == 1)
			return (-1);
		if (res > (long)INT_MAX + 1 && sign == -1)
			return (-1);
	}
	return ((int)(res * sign));
}
