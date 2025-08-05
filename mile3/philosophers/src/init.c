#include "../philo.h"

void init_sim(t_table *table)
{
	table->end_sim = false;
	table->philos = safe_malloc(table->philo_nbr);
}
/*safe mutexes functions*/

void safe_handle_mutex(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		pthread_mutex_lock(mutex);
	else if (opcode == UNLOCK)
		pthread_mutex_unlock(mutex);
	else if (opcode == INIT)
		pthread_mutex_init(mutex, NULL);
	else if (opcode == DESTROY)
		pthread_mutex_destroy(mutex);
	
}