/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 23:34:11 by ppaula-s          #+#    #+#             */
/*   Updated: 2026/03/31 21:37:20 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>
# include <stdint.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				philo_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				limit_meals;
	bool			simulation_end;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	end_mutex;
	t_philo			*philos;
}	t_data;

int		init_forks(t_data *data);
int		init_philosophers(t_data *data);
int		init_mutexes(t_data *data);
int		init_simulation(t_data *data);
void	parse_args(t_data *data, char **av);
void	cleanup_simulation(t_data *data);
int		start_simulation(t_data *data);
int		join_all_philos(t_data *data);
int		create_philosopher_threads(t_data *data);
int		start_monitor_thread(t_data *data, pthread_t *monitor_thread);
bool	check_death(t_data *data);
bool	check_all_ate(t_data *data);
bool	check_simulation_end(t_data *data);
void	cleanup_threads(t_data *data);
void	init_meal_times_inline(t_data *data);
void	*monitor_routine(void *arg);
void	take_forks(t_philo *philo);
void	drop_forks(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	*philosopher_routine(void *arg);
long	get_time(void);
void	ft_usleep(long ms, t_data *data);
void	print_status(t_philo *philo, char *status);
int		ft_atoi(const char *str);
void	ft_error(char *msg);

#endif
