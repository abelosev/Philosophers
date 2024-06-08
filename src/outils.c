#include "../inc/philo.h"

void free_list(t_philo *list)
{
	t_philo *tmp;

	while(list != NULL)
	{
		tmp = list->next;
		// free(list->data); //??
		free(list);
		list = tmp;
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if(!tab)
		return ;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void free_data(t_data *data)
{
	int i;

	i = 0;
	if(data->philos)
		free_list(data->philos);
	if(data->logs)
		free_tab(data->logs);
	pthread_mutex_destroy(&data->print);
	if(data->fork)
	{
		while(i < data->philo_nb)
		{
			pthread_mutex_destroy(&data->fork[i]);
			i++;
		}
	}
	free(data->fork);
	free(data);
}

void ft_print(t_data *data, int index)
{
	u_int64_t time_ms;
	
	pthread_mutex_lock(&data->print);
	time_ms = get_timestamp();
	printf("%llu %d %s\n", time_ms, data->philos->id, data->logs[index]);
	pthread_mutex_unlock(&data->print);
}