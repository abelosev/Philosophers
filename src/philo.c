/*number_of_philosophers time_to_die time_to_eat
time_to_sleep
[number_of_times_each_philosopher_must_eat]*/

#include "philo.h"

int number_of_philosophers = 5;

void *routine(void *arg)
{
	return (NULL);
}

t_philo *philo_create(int *i)
{
	t_philo *ph;

	ph = malloc(sizeof(t_philo));
	if(!ph)
		return (NULL);
	ph->id = *i;
	ph->th = pthread_create(&(ph->th), NULL, routine, NULL);
	if(ph->th != 0)
		return (NULL);
	ph->next = NULL;
	return (ph);
}

// вспомнить, как создавать списки 

t_philo *philo_list(int number_of_philosophers)
{
	int i;
	t_philo *philo_list;

	i = 0;
	philo_list = philo_create(i);

	while(i < number_of_philosophers)
	{
		philo_create(i);

	}

}

int main()
{

}