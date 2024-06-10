#include "../inc/philo.h"

void ft_print(t_philo *ph, int index)
{
	u_int64_t time_ms;
	
	pthread_mutex_lock(&ph->data->print);
	time_ms = get_timestamp();
	if(ph->data->flag_death == true)
		pthread_mutex_unlock(&ph->data->print);
	else if(ph->data->nb_full == ph->data->philo_nb)
		printf("%s\n", ph->data->logs[index]);
	else
		printf("%llu %d %s\n", time_ms, ph->id, ph->data->logs[index]);
	pthread_mutex_unlock(&ph->data->print);
}

u_int64_t get_timestamp()
{
	struct timeval tv;
	u_int64_t time_ms;

	gettimeofday(&tv, NULL);
	time_ms = tv.tv_sec * 1000 + (tv.tv_usec / 1000);
	return (time_ms);
}

int ft_usleep(t_philo *ph, u_int64_t gap)
{
	u_int64_t start;

	start = get_timestamp();
	while(get_timestamp() - start < gap)
	{
		if(ph->data->flag_death == true || ph->data->nb_full == ph->data->philo_nb) //попытка отследить этот флаг в других тредах
			return (1);
		if(get_timestamp() - ph->start_meal >= (u_int64_t)ph->data->time_die)
		{
			ft_print(ph, 5);
			ph->dead = true;
			pthread_mutex_lock(&ph->data->dead); //is it really necessary?
			ph->data->flag_death = true;
			pthread_mutex_unlock(&ph->data->dead);
			return (1);
		}
		usleep(100);
	}
	return (0);
}