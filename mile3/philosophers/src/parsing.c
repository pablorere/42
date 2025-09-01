/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42urduliz.com   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 04:33:58 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/08/04 04:33:58 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static inline bool	is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

static long	ft_atol(const char *str)
{
	long	result;

	result = 0;
	while (is_space(*str))
		str++;
	if (*str == '-')
		return (-1);
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (result > (LONG_MAX - (*str - '0')) / 10)
			return (-1);
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result);
}

void	parse(t_table *table, char **av)
{
	table->philo_nbr = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1e3;
	table->time_to_eat = ft_atol(av[3]) * 1e3;
	table->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (table->time_to_die < 6e4
		|| table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		ft_errors("give at least 60ms to each parameter");
	if (av[5])
		table->limit_meals = ft_atol(av[5]);
	else
		table->limit_meals = -1;
}
