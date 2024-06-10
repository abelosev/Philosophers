#include "../inc/philo.h"

t_philo *philo_create(int i, t_data *data)
{
	t_philo *ph;

	ph = malloc(sizeof(t_philo));
	if(!ph)
		return (NULL);
	ph->id = i;
	ph->had_meals = 0;
	ph->start_meal = 0; //should I add a mutex here?
	ph->data = data;
	ph->dead = false;
	if(pthread_create(&(ph->th), NULL, routine, (void *)ph))
		return (NULL);
	ph->next = NULL;
	return (ph);
}

t_philo *philo_list(t_data *data)
{
	int i;
	t_philo *begin;
	t_philo *curr;

	begin = philo_create(1, data); //because I don't want an id = 0 at all
	curr = begin;
	i = 2;
	while(i <= data->philo_nb)
	{
		curr->next = philo_create(i, data);
		if(!curr->next)
		{
			free_list(begin);
			return (NULL);
		}
		curr = curr->next;
		i++;
	}
	return (begin);
}
