#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/wait.h>

typedef struct s_philo
{
	int id;
	pthread_t th;
	pthread_mutex_t mutex;
	struct s_philo *next;
} t_philo;

typedef struct s_data
{
	int philo_nb;
	long long int time_die;
	long long int time_eat;
	long long int time_sleep;
	int	meal_nb;

} t_data;

void	free_list(t_philo *list);
int		ft_atoi(const char *str);
t_philo *philo_list(t_data *data);

#endif