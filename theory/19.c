// Deadlocks in C

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

#define THREAD_NUM 8

pthread_mutex_t mutexFuel;
int fuel = 50;
pthread_mutex_t mutexWater;
int water = 10;

void *routine(void *arg)
{
	pthread_mutex_lock(&mutexFuel);
	pthread_mutex_lock(&mutexWater);
	// pthread_mutex_lock(&mutexFuel); // - simple way to cause a deadlock
	sleep(1);
	fuel += 50;
	water = fuel;
	printf("Finished\n");
	pthread_mutex_unlock(&mutexWater);
	pthread_mutex_unlock(&mutexFuel);
	return(NULL);
}

int main()
{
	pthread_t th[THREAD_NUM];
	int i;

	pthread_mutex_init(&mutexFuel, NULL);
	pthread_mutex_init(&mutexWater, NULL);
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
	printf("Fuel = %d\n", fuel);
	printf("Water = %d\n", water);
	pthread_mutex_destroy(&mutexFuel);
	pthread_mutex_destroy(&mutexWater);
	return (0);
}