#include "../philo.h"

void init_sim(t_table *table)
{
	table->end_sim = false;
	table->philos = safe_malloc(table->philo_nbr);
}
/*safe mutexes functions*/

