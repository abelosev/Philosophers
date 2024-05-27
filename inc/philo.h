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
	t_philo *next;
} t_philo;

#endif