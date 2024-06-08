#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <limits.h>

typedef struct s_philo
{
	int id;
	int meals; //сколько meals было
	// int flag;
	pthread_t th;
	pthread_mutex_t mutex;
	struct s_philo *next;
} t_philo;

typedef struct s_data
{
	int philo_nb;
	int flag_fin; 
	long long int time_die;
	long long int time_eat;
	long long int time_sleep;
	int	meal_nb;
	t_philo *philos;
} t_data;

//outils
void		free_list(t_philo *list);
int			ft_atoi_modif(const char *str);
bool		check_nbr(const char *str, int *res);
bool		check_input(int ac, char **av);

//
t_philo		*philo_list(t_data *data);

//time
long int	get_timestamp(void);

#endif