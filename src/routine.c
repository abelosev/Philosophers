/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:05:30 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/11 13:15:51 by abelosev         ###   ########.fr       */
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

void forks_index(t_philo *ph, int *l_index, int *r_index)
{
	*l_index = ph->id - 1;
	if (ph->id == 1)
		*r_index = ph->data->philo_nb - 1;
	else
		*r_index = ph->id - 2;
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
	forks_index(ph, &l_index, &r_index);
	if(ph->id % 2 == 0)
	{
		if(ft_usleep(ph, 10))
			return ((void *)ph);
	}
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
