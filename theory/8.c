// Practical example for using threads #1 (Summing numbers from an array)

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void *sum_count(void *arg)
{
	int start = *(int *)arg;
	int i = 0;
	int sum = 0;
	while(i < 5)
	{
		sum += primes[start + i];
		i++;
	}
	*(int *)arg = sum;
	return arg;
}

int main()
{
	pthread_t th[2];
	int i;
	int globalSum;
	// int *res;
	int *a;

	i = 0;
	while(i < 2)
	{
		a = malloc(sizeof(int));
		if(!a)
			return (1);
		*a = i * 5;
		if(pthread_create(&th[i], NULL, &sum_count, a))
		{
			free(a);
			return (1);
		}
		i++;
	}
	i--;
	globalSum = 0;
	while(i >= 0)
	{
		if(pthread_join(th[i], (void **)&a) != 0)
		{
			printf("HERE %d\n", i);
			free(a);
			return (1);
		}
		globalSum += *a;
		i--;
		free(a);
	}
	printf("Global sum : %d\n", globalSum);
	return (0);
	// free(res);
}



//Первый вариант решения:

// int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
// // pthread_mutex_t mutex;

// void *sum(void *arg)
// {
// 	int index = *(int *)arg + 4;
// 	int i = *(int *)arg;
// 	int *sum = malloc(sizeof(int));
// 	if(!sum)
// 		return (NULL);
// 	*sum = 0;
// 	// pthread_mutex_lock(&mutex);
// 	while(i <= index)
// 	{
// 		*sum = *sum + primes[i];
// 		i++;
// 	}
// 	// pthread_mutex_unlock(&mutex);
// 	return ((void *)sum);
// }

// int main()
// {
// 	pthread_t t1, t2;
// 	int *a1;
// 	int *a2;
// 	int *res1;
// 	int *res2;

// 	// pthread_mutex_init(&mutex, NULL);
// 	a1 = malloc(sizeof(int));
// 	if(!a1)
// 		return (1);
// 	*a1 = 0;
// 	a2 = malloc(sizeof(int));
// 	if(!a2)
// 		return (1);
// 	*a2 = 5;

// 	if (pthread_create(&t1, NULL, sum, (void *)a1))
// 		return (1);
// 	if (pthread_create(&t2, NULL, sum, (void *)a2))
// 		return (1);
	
// 	if (pthread_join(t1, (void **)&res1))
// 		return (2);
// 	printf("Result1 %d\n", *res1);
// 	if (pthread_join(t2, (void **)&res2))
// 		return (2);
// 	printf("Result2 %d\n", *res2);
// 	*(int *)res1 = *(int *)res1 + *(int *)res2;
// 	printf("Result %d\n", *res1);
// 	free(res1);
// 	free(res2);
// 	free(a1);
// 	free(a2);
// 	// pthread_mutex_destroy(&mutex);
// 	return (0);
// }