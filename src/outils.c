#include "../inc/philo.h"

void free_list(t_philo *list)
{
	t_philo *tmp;

	while(list != NULL)
	{
		tmp = list->next;
		pthread_mutex_destroy(&(list->mutex));
		free(list);
		list = tmp;
	}
}

bool check_input(int ac, char **av)
{
	int i;
	int res;

	i = 1;
	res = 0;
	if(ac < 5 || ac > 6)
	{
		printf("The number of args is not correct\n");
		return (false);
	}
	while(i < ac)
	{
		if(!check_nbr(av[i], &res))
		{
			printf("At least one of the args is not correct\n");
			return (false);
		}
		if(i == 1 && res > 200)
		{
			printf("The nb of philos should be less than 200\n");
			return (false);
		}
		if(i != 5 && res == 0)
		{
			printf("This args can't be equal to '0'\n");
			return (false);
		}
		res = 0;
		i++;
	}
	return (true);
}