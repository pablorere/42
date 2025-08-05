#include "philo.h"

void *safe_malloc(size_t bytes)
{
	void *ret;

	ret = malloc(bytes);
	if (ret == NULL)
		ft_errors("Malloc has failed");
	return(ret);
}