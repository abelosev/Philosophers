// Difference between trylock and lock in C

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

pthread_mutex_t mutex;

void *routine(void *arg)
{
	if (pthread_mutex_trylock(&mutex) == 0) //return 0 if success
	{
		printf("Got lock\n");
		sleep(1);
		pthread_mutex_unlock(&mutex);
	}
	else
		printf("Was already locked\n");
	return (NULL);
}

int main()
{
	pthread_t th[4];
	int i;

	pthread_mutex_init(&mutex, NULL);
	i = 0;
	while (i < 4)
	{
		if (pthread_create(&th[i], NULL, routine, NULL))
			return (1);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (pthread_join(th[i], NULL))
			return (1);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	return 0;
}