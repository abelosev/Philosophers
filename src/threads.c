#include "../inc/philo.h"

void *routine(void *arg)
{
	t_data *data;

	data = (t_data *)arg;

	// pthread_mutex_lock();
	printf("X has taken a fork\n");
	usleep(data->time_eat);
	// pthread_mutex_unlock(&(all->ph->mutex));
	printf("X is sleeping\n");
	// fonction pour interrompre le sommeil
	usleep(data->time_sleep); // может прервать сон (чекать в процессе)
	//to start thinking (?)
	printf("X is thinking\n");
	return (NULL);
}

t_philo *philo_create(int i, t_data *data)
{
	t_philo *ph;

	ph = malloc(sizeof(t_philo));
	if(!ph)
		return (NULL);
	ph->id = i;
	if(pthread_create(&(ph->th), NULL, routine, (void **)&data))
		return (NULL);
	pthread_mutex_init(&(ph->mutex), NULL);
	ph->next = NULL;
	return (ph);
}

t_philo *philo_list(t_data *data)
{
	int i;
	t_philo *begin;
	t_philo *curr;

	begin = philo_create(0, data);
	curr = begin;
	i = 1;
	while(i < data->philo_nb)
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