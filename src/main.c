
#include "../inc/philo.h"

t_data *init_data(char **av)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if(!data)
		return (NULL);
	data->philo_nb = ft_atoi_modif(av[1]);
	data->time_die = ft_atoi_modif(av[2]);
	data->time_eat = ft_atoi_modif(av[3]);
	data->time_sleep = ft_atoi_modif(av[4]);
	if(av[5])
		data->meal_nb = ft_atoi_modif(av[5]);
	else
		data->meal_nb = 0;				// насколько это необходимо?
	return (data);
}

int main(int ac, char **av)
{
	t_data *data;
	t_philo *list;
	t_philo *start;

	if(!check_input(ac, av))
		return (1);
	data = init_data(av);
	list = philo_list(data);
	start = list;
	while(list != NULL)
	{
		if(pthread_join(list->th, NULL))
		{
			free_list(list);
			return (1);
		}
		list = list->next;
	}
	free_list(start);
	free(data);
	return (0);
}