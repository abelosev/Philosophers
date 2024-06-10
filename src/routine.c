/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:05:30 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/10 18:05:31 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void *routine(void *arg)
{
	t_philo *ph;
	int l_index;
	int r_index;

	ph = (t_philo *)arg;
	ph->start_meal = ph->data->start_simul; //starting time of the simulation

	if(ph->data->philo_nb == 1)
	{
		ft_print(ph, 5);
		ph->dead = true;
		pthread_mutex_lock(&ph->data->dead); //is it really necessary?
		ph->data->flag_death = true;
		pthread_mutex_unlock(&ph->data->dead);
		return (void *)ph; //?
	}

	l_index = ph->id - 1;
	if(ph->id == 1)
		r_index = ph->data->philo_nb - 1;
	else
		r_index = ph->id - 2;

	while(1) //&& ph->had_meals < ph->data->meal_nb)
	{
		if(ph->id % 2 != 0)
		{
			pthread_mutex_lock(&ph->data->fork[l_index]); //left
			ft_print(ph, 0);
			pthread_mutex_lock(&ph->data->fork[r_index]); //right (- 1 because I number my philos from 1)
			ft_print(ph, 1);
		}
		else if(ph->id % 2 == 0)
		{
			pthread_mutex_lock(&ph->data->fork[r_index]); //right
			ft_print(ph, 1);
			pthread_mutex_lock(&ph->data->fork[l_index]); //left
			ft_print(ph, 0);
		}
		ph->start_meal = get_timestamp(); //is this placement correct?
		ft_print(ph, 2);
		if(ft_usleep(ph, ph->data->time_eat))
		{
			pthread_mutex_unlock(&ph->data->fork[l_index]);
			pthread_mutex_unlock(&ph->data->fork[r_index]); //right (- 1 because I number my philos from 1)
			break ;
		}
		pthread_mutex_unlock(&ph->data->fork[r_index]);
		pthread_mutex_unlock(&ph->data->fork[l_index]);

		ph->had_meals++;
		if(ph->data->meal_nb != 0 && ph->had_meals == ph->data->meal_nb)
		{
			pthread_mutex_lock(&(ph->data->full));
			ph->data->nb_full++;
			pthread_mutex_unlock(&(ph->data->full));
			break ;										// enlever le break 
		}
		ft_print(ph, 3);
		if(ft_usleep(ph, ph->data->time_sleep))
			break ;
		ft_print(ph, 4);
	}
	if(ph->data->meal_nb != 0 && ph->data->nb_full == ph->data->philo_nb)
		ft_print(ph, 6);
	return (void *)ph; // верно ли это
}