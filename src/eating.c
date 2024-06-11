/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:13:27 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/11 13:23:11 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
	if(ft_print(ph, 1))
	{
		pthread_mutex_unlock(&ph->data->fork[r_index]);
		pthread_mutex_unlock(&ph->data->fork[l_index]);
		return (1);	
	}
	ph->had_meals++;
	pthread_mutex_lock(&ph->data->full);
	if (ph->had_meals == ph->data->meal_nb)
		ph->data->nb_full++;
	pthread_mutex_unlock(&ph->data->full);
	if (ft_usleep(ph, ph->data->time_eat))
	{
		pthread_mutex_unlock(&ph->data->fork[r_index]);
		pthread_mutex_unlock(&ph->data->fork[l_index]);
		return (1);
	}
	pthread_mutex_unlock(&ph->data->fork[r_index]);
	pthread_mutex_unlock(&ph->data->fork[l_index]);
	if (end_simul(ph) != 0)
		return (1);
	return (0);
}

int	eating(t_philo *ph, int l_index, int r_index)
{
	if(ph->id == ph->data->philo_nb)
	{
		if (taking_fork(ph, r_index))
		return (1);	
		if (taking_fork(ph, l_index))
		{
			pthread_mutex_unlock(&ph->data->fork[r_index]);
			return (1);
		}
	}
	else
	{
		if (taking_fork(ph, l_index))
		return (1);	
		if (taking_fork(ph, r_index))
		{
			pthread_mutex_unlock(&ph->data->fork[l_index]);
			return (1);
		}
	}
	if (forks_taken(ph, l_index, r_index))
		return (1);
	return (0);
}

// int	eating(t_philo *ph, int l_index, int r_index)
// {
// 	if (ph->id % 2 != 0)
// 	{
// 		if (taking_fork(ph, l_index))
// 			return (1);
// 		if (taking_fork(ph, r_index))
// 		{
// 			pthread_mutex_unlock(&ph->data->fork[l_index]);
// 			return (1);
// 		}
// 	}
// 	else if (ph->id % 2 == 0)
// 	{
// 		if (taking_fork(ph, r_index))
// 			return (1);
// 		if (taking_fork(ph, l_index))
// 		{
// 			pthread_mutex_unlock(&ph->data->fork[r_index]);
// 			return (1);	
// 		}
// 	}
// 	if (forks_taken(ph, l_index, r_index))
// 		return (1);
// 	return (0);
// }
