#include "../inc/philo.h"

void *routine(void *arg)
{
	t_philo *ph;

	ph = (t_philo *)arg;
	ph->end_meal = get_timestamp(); //starting time
	while(ph->data->flag_death == false)
	{
		if(ph->id % 2 != 0)
		{
			pthread_mutex_lock(&ph->data->fork[ph->id]); //left
			ft_print(ph, 0);
			pthread_mutex_lock(&ph->data->fork[ph->id - 1]); //right (- 1 because I number my philos from 1)
			ft_print(ph, 1);
		}
		else if(ph->id % 2 == 0)
		{
			pthread_mutex_lock(&ph->data->fork[ph->id - 1]); //right
			ft_print(ph, 1);
			pthread_mutex_lock(&ph->data->fork[ph->id]); //left
			ft_print(ph, 0);
		}
		ft_print(ph, 2);
		if(ft_usleep(ph, ph->data->time_eat))
		{
			pthread_mutex_unlock(&ph->data->fork[ph->id]);
			pthread_mutex_unlock(&ph->data->fork[ph->id - 1]);
			break ;
		}
		pthread_mutex_unlock(&ph->data->fork[ph->id]);
		pthread_mutex_unlock(&ph->data->fork[ph->id - 1]);

		ph->end_meal = get_timestamp();
		ph->had_meals++;
		if(ph->data->meal_nb != 0 && ph->had_meals == ph->data->meal_nb)
		{
			ph->data->nb_full++;
			break ;
		}
		ft_print(ph, 3);
		if(ft_usleep(ph, ph->data->time_sleep))
			break ;
		ft_print(ph, 4);

		// if(get_timestamp() - ph->end_meal >= (u_int64_t)ph->data->time_die) //do I actually need it here?
		// {
		// 	ft_print(ph, 5);
		// 	ph->data->flag_death = true;
		// 	break ;
		// }
	}
	return (void *)ph;
}