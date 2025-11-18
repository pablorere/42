#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>
#include "mini_philo.h"


/* ========== UTILS ========== */

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(int ms)
{
	long	start;

	start = get_time();
	while (get_time() - start < ms)
		usleep(100);
}

void	print_status(t_philo *philo, char *status, long timestamp)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!philo->data->end_sim)
		printf("%ld %d %s\n", timestamp, philo->id, status);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

/* ========== INIT ========== */

void	init_data(t_data *data, int philo_nbr)
{
	int	i;

	data->philo_nbr = philo_nbr;
	data->time_to_die = 800;
	data->time_to_eat = 200;
	data->time_to_sleep = 200;
	data->limit_meals = -1;
	data->end_sim = false;
	data->start_time = get_time();

	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);

	data->forks = malloc(sizeof(pthread_mutex_t) * philo_nbr);
	data->philos = malloc(sizeof(t_philo) * philo_nbr);

	i = 0;
	while (i < philo_nbr)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}

	i = 0;
	while (i < philo_nbr)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = get_time();
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % philo_nbr];
		data->philos[i].data = data;
		i++;
	}
}

/* ========== ROUTINE ========== */

void	philo_eat(t_philo *philo, t_data *data)
{
	long	timestamp;

	pthread_mutex_lock(philo->left_fork);
	timestamp = get_time() - data->start_time;
	print_status(philo, "has taken a fork", timestamp);

	pthread_mutex_lock(philo->right_fork);
	timestamp = get_time() - data->start_time;
	print_status(philo, "has taken a fork", timestamp);

	timestamp = get_time() - data->start_time;
	print_status(philo, "is eating", timestamp);

	pthread_mutex_lock(&data->meal_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&data->meal_mutex);

	ft_usleep(data->time_to_eat);

	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	long	timestamp;

	philo = (t_philo *)arg;
	data = philo->data;

	if (philo->id % 2 == 0)
		ft_usleep(100);

	while (!data->end_sim)
	{
		timestamp = get_time() - data->start_time;
		print_status(philo, "is thinking", timestamp);
		ft_usleep(THINK_TIME);

		philo_eat(philo, data);

		timestamp = get_time() - data->start_time;
		print_status(philo, "is sleeping", timestamp);
		ft_usleep(SLEEP_TIME);
	}
	return (NULL);
}

/* ========== SIMULATION ========== */

void	start_simulation(t_data *data)
{
	int	i;

	printf("=== Mini Philosophers ===\n");
	printf("%d philosophers\n", data->philo_nbr);
	printf("Starting simulation...\n\n");

	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_create(&data->philos[i].thread, NULL,
					   philosopher_routine, &data->philos[i]);
		i++;
	}

	sleep(10);
	data->end_sim = true;

	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

void	cleanup_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->meal_mutex);

	free(data->forks);
	free(data->philos);

	printf("\n=== Simulation ended ===\n");
	printf("Meals eaten by each philosopher:\n");
	i = 0;
	while (i < data->philo_nbr)
	{
		printf("Philosopher %d: %d meals\n",
			   data->philos[i].id, data->philos[i].meals_eaten);
		i++;
	}
}

/* ========== MAIN ========== */

int	main(int argc, char **argv)
{
	t_data	data;
	int		philo_nbr;

	if (argc != 2)
	{
		printf("Usage: ./mini_philo <number_of_philosophers>\n");
		return (1);
	}

	philo_nbr = atoi(argv[1]);
	if (philo_nbr < 1 || philo_nbr > 200)
	{
		printf("Number of philosophers must be between 1 and 200\n");
		return (1);
	}

	init_data(&data, philo_nbr);
	start_simulation(&data);
	cleanup_data(&data);

	return (0);
}
