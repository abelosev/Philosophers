// Practical example for pthread_mutex_trylock

// If we have more than one stove : 

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

pthread_mutex_t stoveMutexes[4];
int stoveFuel[4] = {100, 100, 100, 100};

void *routine()
{
	int fuelNeeded;
	int i;

	i = 0;
	while(i < 4)
	{
		if(pthread_mutex_trylock(&stoveMutexes[i]) == 0)
		{
			fuelNeeded = rand() % 50;
			printf("Fuel needed %d - \n", fuelNeeded);
			if(stoveFuel[i] - fuelNeeded > 0)
			{
				stoveFuel[i] -= fuelNeeded;
				usleep(1000000);
				printf("Fuel left %d in the stove number %d\n", stoveFuel[i], i);
			}
			else
				printf("No fuel left for this chef in this stove\n");
			pthread_mutex_unlock(&stoveMutexes[i]);
			break ;
		}
		else if (i == 3)
		{
			usleep(300000);
			i = 0;
		}
		i++;
	}
	return (NULL);
}


int main()
{
	pthread_t chef[10];
	int i;

	i = 0;
	while(i < 4)
	{
		pthread_mutex_init(&(stoveMutexes[i]), NULL);
		i++;
	}
	srand(time(NULL));
	i = 0;
	while(i < 10)
	{
		if (pthread_create(&chef[i], NULL, routine, NULL))
			return (1);
		i++;
	}
	i = 0;
	while(i < 10)
	{
		if (pthread_join(chef[i], NULL))
			return (1);
		printf("chef number %d has finished\n", i);
		i++;
	}
	i = 0;
	while(i < 4)
	{
		pthread_mutex_destroy(&(stoveMutexes[i]));
		i++;
	}
	return (0);
}




// If we have one stove : 

// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <unistd.h>
// #include <errno.h>
// #include <time.h>

// pthread_mutex_t stoveMutex;
// int stoveFuel = 100;

// void *routine(void *arg)
// {
// 	int id;
// 	int fuelNeeded;

// 	pthread_mutex_lock(&stoveMutex);
// 	id = *(int *)arg;
// 	fuelNeeded = rand() % 30;
// 	printf("Fuel needed %d  ", fuelNeeded);
// 	if(stoveFuel - fuelNeeded > 0)
// 	{
// 		stoveFuel -= fuelNeeded;
// 		usleep(100000);
// 		printf("Fuel left %d\n", stoveFuel);
// 	}
// 	else
// 		printf("No fuel left for this chef\n");
// 	pthread_mutex_unlock(&stoveMutex);
// 	*(int *)arg = stoveFuel;
// 	return (arg);
// }


// int main()
// {
// 	pthread_t chef[10];
// 	int i;
// 	int *res;

// 	pthread_mutex_init(&stoveMutex, NULL);
// 	srand(time(NULL));
// 	i = 0;
// 	while(i < 10)
// 	{
// 		res = malloc(sizeof(int));
// 		if(!res)
// 			return (1);
// 		if (pthread_create(&chef[i], NULL, routine, (void *)res))
// 			return (1);
// 		i++;
// 	}
// 	i = 0;
// 	while(i < 10)
// 	{
// 		if (pthread_join(chef[i], (void **)&res))
// 			return (1);
// 		free(res);
// 		i++;
// 	}
// 	printf("stoveFuel %d\n", stoveFuel);
// 	pthread_mutex_destroy(&stoveMutex);
// 	return (0);
// }