
#include "../inc/philo.h"

int main(int ac, char **av)
{
	t_data *data;
	t_philo *list;
	t_philo *start;

	if(!check_input(ac, av))
		return (1);
	data = malloc(sizeof(t_data));
	if(!data)
		return (1);
	if(init_data(data, av))
	{
		free_data(data);
		return (1);
	}
	list = philo_list(data);
	start = list;
	while(list != NULL)
	{
		if(pthread_join(list->th, NULL))
		{
			free_data(data);
			return (1);
		}
		list = list->next;
	}
	free_data(data);
	return (0);
}