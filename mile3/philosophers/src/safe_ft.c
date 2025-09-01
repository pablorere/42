#include "philo.h"

void *safe_malloc(size_t bytes)
{
	void *ret;

	ret = malloc(bytes);
	if (ret == NULL)
		ft_errors("Malloc has failed");
	return(ret);
}

static handle_opcode_mutex()

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
	else 
		ft_errors("wrong opcode to mutex handle");
}
