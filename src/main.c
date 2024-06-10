/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:05:21 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/10 18:29:17 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	get_data(t_data *data, char **av)
{
	if (init_data(data, av))
	{
		free_data(data);
		return (1);
	}
	data->philos = philo_list(data);
	if (!data->philos)
	{
		free_data(data);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*start;

	if (!check_input(ac, av))
		return (1);
	data = malloc(sizeof(t_data));
	if (!data || get_data(data, av))
		return (1);
	start = data->philos;
	while (start != NULL)
	{
		if (pthread_join(start->th, NULL))
		{
			free_data(data);
			return (1);
		}
		start = start->next;
	}
	free_data(data);
	return (0);
}
