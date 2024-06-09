#include "../inc/philo.h"

t_philo *philo_create(int i, t_data *data)
{
	t_philo *ph;

	ph = malloc(sizeof(t_philo));
	if(!ph)
		return (NULL);
	ph->id = i;
	ph->had_meals = 0;
	ph->end_meal = 0;
	ph->data = data;
	if(pthread_create(&(ph->th), NULL, routine, (void *)ph))
		return (NULL);
	ph->next = NULL;
	return (ph);
}

t_philo *philo_list(t_data *data)
{
	int i;
	t_philo *begin;
	t_philo *curr;

	begin = philo_create(1, data); //I don't want a id = 0 at all
	curr = begin;
	i = 2;
	while(i <= data->philo_nb)
	{
		curr->next = philo_create(i, data);
		if(!curr->next)
		{
			free_list(begin);
			return (NULL);
		}
		curr = curr->next;
		i++;
	}
	return (begin);
}

void init_args(t_data *data, char **av)
{
	data->philo_nb = ft_atoi_modif(av[1]);
	data->time_die = ft_atoi_modif(av[2]);
	data->time_eat = ft_atoi_modif(av[3]);
	data->time_sleep = ft_atoi_modif(av[4]);
	if(av[5])
		data->meal_nb = ft_atoi_modif(av[5]);
	else
		data->meal_nb = 0;				// или -1 ?
}

int init_logs(t_data *data)
{
	data->logs = malloc(sizeof(char *) * 7);
	if(!data->logs)
		return (1);
	data->logs[0] = ft_strdup("has taken a left fork\n");
	data->logs[1] = ft_strdup("has taken a right fork\n");
	data->logs[2] = ft_strdup("is eating\n");
	data->logs[3] = ft_strdup("is sleeping\n");
	data->logs[4] = ft_strdup("is thinking\n");
	data->logs[5] = ft_strdup("died\n");
	data->logs[6] = NULL;
	return (0);
}

int init_mutexes(t_data *data)
{
	int i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
	if(!data->fork)
		return (1);
	while(i < data->philo_nb)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print, NULL);
	return (0);
}

int init_data(t_data *data, char **av)
{
	init_args(data, av);
	data->flag_death = false;
	data->nb_full = 0;
	data->philos = philo_list(data);
	if(!data->philos)
		return (1);
	if(init_logs(data))
		return (1);
	if(init_mutexes(data))
		return (1);
	return (0);
}