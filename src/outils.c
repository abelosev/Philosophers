#include "../inc/philo.h"

void free_list(t_philo *list)
{
	t_philo *tmp;

	while(list != NULL)
	{
		tmp = list->next;
		pthread_mutex_destroy(&(list->mutex));
		free(list);
		list = tmp;
	}
}
