/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_outils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:05:36 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/10 18:49:45 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

u_int64_t	get_timestamp()
{
	struct timeval	tv;
	u_int64_t		time_ms;

	gettimeofday(&tv, NULL);
	time_ms = tv.tv_sec * 1000 + (tv.tv_usec / 1000);
	return (time_ms);
}

int	end_simul(t_philo *ph)
{
	int	res;
	
	pthread_mutex_lock(&ph->data->dead);
	pthread_mutex_lock(&(ph->data->full));
	if(get_timestamp() - ph->start_meal >= (u_int64_t)ph->data->time_die)
		ph->data->flag_death = true;
	if (ph->data->flag_death)
		res = 1;
	else if (ph->data->meal_nb != 0 && ph->data->nb_full == ph->data->philo_nb)
		res = 2;
	else
		res = 0;
	pthread_mutex_unlock(&(ph->data->full));
	pthread_mutex_unlock(&ph->data->dead);
	return (res);
}

int	ft_print(t_philo *ph, int index)
{
	u_int64_t	time_ms;

	pthread_mutex_lock(&ph->data->print);
	time_ms = get_timestamp();
	pthread_mutex_lock(&ph->data->dead);
	if(ph->data->flag_death)
	{
		// printf("%s\n", ph->data->logs[5]);
		pthread_mutex_unlock(&ph->data->print);
		pthread_mutex_unlock(&ph->data->dead);			// fonction separee pour check flag_dead
		// return ;
	}
	else if(ph->data->meal_nb != 0 && ph->data->nb_full == ph->data->philo_nb) /// proteger !!
	{
		printf("%s\n", ph->data->logs[index]);
		pthread_mutex_unlock(&ph->data->dead);
	}
	else
	{
		printf("%lu %d %s\n", time_ms, ph->id, ph->data->logs[index]);
		pthread_mutex_unlock(&ph->data->dead);
	}
	pthread_mutex_unlock(&ph->data->print);
	return (0);
}

int ft_usleep(t_philo *ph, u_int64_t gap)
{
	u_int64_t start;

	start = get_timestamp();
	while(get_timestamp() - start < gap)
	{
		pthread_mutex_lock(&ph->data->dead);
		if(ph->data->flag_death || ph->data->nb_full == ph->data->philo_nb) //попытка отследить этот флаг в других тредах
		{
			pthread_mutex_unlock(&ph->data->dead); 				// !!!
			return (1);
		}
		pthread_mutex_unlock(&ph->data->dead);
		if(get_timestamp() - ph->start_meal >= (u_int64_t)ph->data->time_die)
		{
			ft_print(ph, 5);
			pthread_mutex_lock(&ph->data->dead); //is it really necessary?
			ph->data->flag_death = true;
			pthread_mutex_unlock(&ph->data->dead);
			return (1);
		}
		usleep(100);
	}
	return (0);
}