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
#include <stdint.h>

typedef struct s_philo
{
	int id;
	pthread_t th;
	int had_meals;
	//bool dead;
	u_int64_t end_meal;
	struct s_data *data;
	struct s_philo *next;
} t_philo;

typedef struct s_data
{
	int philo_nb;
	int time_die;
	int time_eat;
	int time_sleep;
	int	meal_nb;
	t_philo *philos;
	bool flag_death;
	int nb_full;
	pthread_mutex_t *fork;
	pthread_mutex_t print;
	char **logs;
} t_data;

//outils
void		free_list(t_philo *list);
void		free_data(t_data *data);
int			ft_atoi_modif(const char *str);
bool		check_nbr(const char *str, int *res);
bool		check_input(int ac, char **av);
char		*ft_strdup(const char *s1);
void		ft_print(t_philo *ph, int index);
void		*routine(void *arg);
u_int64_t	get_timestamp(void);
t_philo		*philo_list(t_data *data);
int			init_data(t_data *data, char **av);
t_philo		*philo_list(t_data *data);
int			ft_usleep(t_philo *ph, u_int64_t gap);

#endif