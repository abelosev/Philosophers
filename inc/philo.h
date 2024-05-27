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
	struct s_philo *next;
} t_philo;

// typedef struct s_data
// {
// 	int philo_nb;
// 	// time_to_die
// 	// time_to_eat
// 	// time_to_sleep
// 	// [number_of_times_each_philosopher_must_eat]

// } t_data;

void	free_list(t_philo *list);

#endif