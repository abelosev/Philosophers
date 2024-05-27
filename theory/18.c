// Static initializers in the PTHREAD API

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

#define THREAD_NUM 2

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //woudn't work for an array

void *routine(void *arg)
{
	pthread_mutex_lock(&mutex);
	sleep(1);
	printf("Finished\n");
	pthread_mutex_unlock(&mutex);
	return(NULL);
}

int main()
{
	pthread_t th[THREAD_NUM];
	int i;

	// pthread_mutex_init(&mutex, NULL); NO NEED TO CALL IT THANKS TO THE defined var
	i = 0;
	while(i < THREAD_NUM)
	{
		if(pthread_create(&th[i], NULL, routine, NULL) != 0)
			perror("Failed to create a thread\n");
		i++;
	}
	i = 0;
	while(i < THREAD_NUM)
	{
		if(pthread_join(th[i], NULL) != 0)
			perror("Failed to join a thread\n");
		i++;
	}
	pthread_mutex_destroy(&mutex);
	return (0);
}