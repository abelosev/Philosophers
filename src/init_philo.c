/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:05:08 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/10 18:18:41 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_philo	*philo_create(int i, t_data *data)
{
	t_philo	*ph;

	ph = malloc(sizeof(t_philo));
	if (!ph)
		return (NULL);
	ph->id = i;
	ph->had_meals = 0;
	ph->start_meal = 0;
	ph->data = data;
	if (pthread_create(&(ph->th), NULL, routine, (void *)ph))
		return (NULL);
	ph->next = NULL;
	return (ph);
}

t_philo	*philo_list(t_data *data)
{
	int		i;
	t_philo	*begin;
	t_philo	*curr;

	begin = philo_create(1, data);
	curr = begin;
	i = 2;
	while (i <= data->philo_nb)
	{
		curr->next = philo_create(i, data);
		if (!curr->next)
		{
			free_list(begin);
			return (NULL);
		}
		curr = curr->next;
		i++;
	}
	return (begin);
}
