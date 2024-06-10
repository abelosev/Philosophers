/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:05:30 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/10 19:59:44 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	one_philo(t_philo *ph)
{
	if (ph->data->philo_nb == 1)
	{
		pthread_mutex_lock(&ph->data->dead);
		ph->data->flag_death = true;
		pthread_mutex_unlock(&ph->data->dead);
		death_log(ph);
		return (1);
	}
	return (0);
}

int	taking_fork(t_philo *ph, int f_index)
{
	pthread_mutex_lock(&ph->data->fork[f_index]);
	if (ft_print(ph, 0))
	{
		pthread_mutex_unlock(&ph->data->fork[f_index]);
		return (1);
	}
	return (0);
}

int	forks_taken(t_philo *ph, int l_index, int r_index)
{
	ph->start_meal = get_timestamp();
	ft_print(ph, 1);
	if (ft_usleep(ph, ph->data->time_eat))
	{
		pthread_mutex_unlock(&ph->data->fork[l_index]);
		pthread_mutex_unlock(&ph->data->fork[r_index]);
		return (1);
	}
	pthread_mutex_unlock(&ph->data->fork[r_index]);
	pthread_mutex_unlock(&ph->data->fork[l_index]);
	ph->had_meals++;
	if (end_simul(ph) != 0)
		return (1);
	return (0);
}

int	eating(t_philo *ph, int l_index, int r_index)
{
	if (ph->id % 2 != 0)
	{
		if (taking_fork(ph, l_index))
			return (1);
		if (taking_fork(ph, r_index))
		{
			pthread_mutex_unlock(&ph->data->fork[l_index]);
			return (1);
		}
	}
	else if (ph->id % 2 == 0)
	{
		if (taking_fork(ph, r_index))
			return (1);
		if (taking_fork(ph, l_index))
		{
			pthread_mutex_unlock(&ph->data->fork[r_index]);
			return (1);	
		}
	}
	if (forks_taken(ph, l_index, r_index))
		return (1);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*ph;
	int		l_index;
	int		r_index;

	ph = (t_philo *)arg;
	ph->start_meal = ph->data->start_simul;
	if (one_philo(ph))
		return ((void *)ph);
	l_index = ph->id - 1;
	if (ph->id == 1)
		r_index = ph->data->philo_nb - 1;
	else
		r_index = ph->id - 2;
	while (1)
	{
		if (eating(ph, l_index, r_index))
			break ;
		ft_print(ph, 2);
		if (ft_usleep(ph, ph->data->time_sleep))
			break ;
		ft_print(ph, 3);
	}
	return ((void *)ph);
}
