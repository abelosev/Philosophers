/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_outils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:05:36 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/10 21:30:07 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	death_log(t_philo *ph)
{
	u_int64_t	time_ms;

	pthread_mutex_lock(&ph->data->print);
	time_ms = get_timestamp() - ph->data->start_simul;
	printf("%lu %d %s\n", time_ms, ph->id, ph->data->logs[4]);
	pthread_mutex_unlock(&ph->data->print);
}

void	full_log(t_philo *ph)
{
	u_int64_t	time_ms;

	pthread_mutex_lock(&ph->data->print);
	time_ms = get_timestamp() - ph->data->start_simul;
	printf("%lu %s\n", time_ms, ph->data->logs[5]);
	pthread_mutex_unlock(&ph->data->print);
}

int	end_simul(t_philo *ph)
{
	int	res;

	pthread_mutex_lock(&ph->data->dead);
	pthread_mutex_lock(&(ph->data->full));
	if (ph->data->flag_death)
		res = 1;
	else if (!ph->data->flag_death
		&& get_timestamp() - ph->start_meal >= (u_int64_t)ph->data->time_die)
	{
		ph->data->flag_death = true;
		death_log(ph);
		res = 3;
	}
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

	if (end_simul(ph) != 0)
		return (1);
	pthread_mutex_lock(&ph->data->print);
	time_ms = get_timestamp() - ph->data->start_simul;
	printf("%lu %d %s\n", time_ms, ph->id, ph->data->logs[index]);
	pthread_mutex_unlock(&ph->data->print);
	return (0);
}

int	ft_usleep(t_philo *ph, u_int64_t gap)
{
	u_int64_t	start;

	start = get_timestamp();
	while (get_timestamp() - start < gap)
	{
		if (end_simul(ph) != 0)
			return (1);
		usleep(100);
	}
	return (0);
}
