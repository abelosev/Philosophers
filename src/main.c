
#include "../inc/philo.h"

int main(int ac, char **av)
{
	t_data *data;
	t_philo *start;

	if(!check_input(ac, av))
		exit(EXIT_FAILURE);
	data = malloc(sizeof(t_data));
	if(!data)
		exit(EXIT_FAILURE);
	if(init_data(data, av))
	{
		free_data(data);
		exit(EXIT_FAILURE);
	}
	data->philos = philo_list(data);
	if(!data->philos)
	{
		free_data(data);
		exit(EXIT_FAILURE);
	}
	start = data->philos;
	while(start != NULL)
	{
		if(pthread_join(start->th, (void **)&(start->data))) //какой аргумент?
		{
			free_data(data);
			exit(EXIT_FAILURE);
		}
		if(((t_philo *)start)->data->flag_death == true || ((t_philo *)start)->data->nb_full == ((t_philo *)start)->data->philo_nb)
		{
			free(data);
			return (0);
		}
		start = start->next;
	}
	free_data(data);
	return (0);
}