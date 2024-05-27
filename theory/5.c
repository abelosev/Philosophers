//How to create threads in a loop (pthread_create)

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int mails = 0;
int nb_of_threads = 4;
pthread_mutex_t mutex;

void *routine()
{
	int i = 0;
	pthread_mutex_lock(&mutex);
	while(i < 100000)
	{
		mails++;
		i++;
	}
	pthread_mutex_unlock(&mutex);
	return (NULL);
}

int main()
{
	pthread_t t[nb_of_threads];
	int i = 0;

	pthread_mutex_init(&mutex, NULL);

	while(i < nb_of_threads)
	{
		if (pthread_create(t + i, NULL, routine, NULL))
			return (1);
		printf("Thread %d started\n", i);
		i++;
	}
	i = 0;
	while(i < nb_of_threads)
	{
		if (pthread_join(*(t + i), NULL))
			return (2);
		printf("Thread %d executed\n", i);
		i++;
	}
	printf("Mails nb : %d\n", mails);
	pthread_mutex_destroy(&mutex);
	return (0);
}