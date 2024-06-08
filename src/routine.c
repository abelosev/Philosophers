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

