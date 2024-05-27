
#include "../inc/philo.h"

void *routine()
{
	usleep(10000);
	printf("thread executed\n");
	return (NULL);
}

t_philo *philo_create(int i)
{
	t_philo *ph;

	ph = malloc(sizeof(t_philo));
	if(!ph)
		return (NULL);
	ph->id = i;
	if(pthread_create(&(ph->th), NULL, routine, NULL))
		return (NULL);
	ph->next = NULL;
	return (ph);
}

t_philo *philo_list(int number_of_philosophers)
{
	int i;
	t_philo *begin;
	t_philo *curr;

	begin = philo_create(0);
	curr = begin;
	i = 1;
	while(i < number_of_philosophers)
	{
		curr->next = philo_create(i);
		if(!curr->next)
		{
			free_list(begin);
			return (NULL);
		}
		curr = curr->next;
		i++;
	}
	// curr->next = NULL;
	return (begin);
}

int main()
{
	int number_of_philosophers = 5;
	t_philo *list = philo_list(number_of_philosophers);
	t_philo *start = list;

	while(list != NULL)
	{
		if(pthread_join(list->th, NULL))
		{
			free_list(list);
			return (1);
		}
		list = list->next;
	}
	free_list(start);
	return (0);
}