
#include "../inc/philo.h"

int main(int ac, char **av)
{
	t_data *data;

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
	while(data->philos != NULL)
	{
		if(pthread_join(data->philos->th, (void **)&(data))) //какой аргумент?
		{
			free_data(data);
			exit(EXIT_FAILURE);
		}
		if(((t_data *)data)->flag_death == true || ((t_data *)data)->nb_full == ((t_data *)data)->philo_nb)
		{
			free(data);
			return (0);
		}
		data->philos = data->philos->next;
	}
	free_data(data);
	return (0);
}