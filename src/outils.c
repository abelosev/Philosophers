#include "../inc/philo.h"

void free_list(t_philo *list)
{
	t_philo *tmp;

	while(list != NULL)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
}
