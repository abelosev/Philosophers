// How to pass arguments to threads in C

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *take_prime(void *arg)
{
	int index = *(int *)arg;
	sleep(index);
	printf("Prime %d index %d\n", primes[index], index);
	free(arg);
	return (NULL);
}

int main()
{
	pthread_t th[10];
	int i;
	int *a;

	i = 0;
	while(i < 10)
	{
		a = malloc(sizeof(int));
		if(!a)
			return (1);
		*a = i;
		if (pthread_create(&(th[i]), NULL, (void *)take_prime, a))
			return (1);
		i++;
	}
	i--;
	while(i > 0)
	{
		if (pthread_join(th[i], NULL))
			return (2);
		i--;
	}
	return (0);
}



// pthread_mutex_t mutex;
// int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

// int *take_prime(void *res)
// {
// 	int *last;
// 	int i;

// 	pthread_mutex_lock(&mutex);
// 	last = (int *)res;
// 	i = 0;
// 	while(i + 1 < 10)
// 	{
// 		if(*last == primes[i])
// 		{
// 			*last = primes[i + 1];
// 			pthread_mutex_unlock(&mutex);
// 			return (last);
// 		}
// 		i++;
// 	}
// 	pthread_mutex_unlock(&mutex);
// 	return (NULL);
// }

// int main()
// {
// 	pthread_t th[10];
// 	int *res;
// 	int i = 0;

// 	pthread_mutex_init(&mutex, NULL);
// 	res = malloc(sizeof(int));
// 	if(!res)
// 		return (1);
// 	*res = 0;
// 	while(i < 10)
// 	{
// 		if (pthread_create(&(th[i]), NULL, (void *)take_prime, (void *)res))
// 			return (1);
// 		i++;
// 	}
// 	i = 0;
// 	while(i < 10)
// 	{
// 		if (pthread_join(th[i], (void **)&res))
// 			return (2);
// 		i++;
// 	}
// 	printf("Result from main %d\n", *res);
// 	free(res);
// 	pthread_mutex_destroy(&mutex);
// 	return (0);
// }
