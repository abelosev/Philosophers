// What is pthread_exit?

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

void *routine(void *res)
{
	*(int *)res = rand() % 20;
	printf("Res in routine %d\n", *(int *)res);
	pthread_exit((void *)res); //можно использовать вместо return
}

int main()
{
	pthread_t th;
	int *res;

	srand(time(NULL));
	res = malloc(sizeof(int));
	if(!res)
		return (1);
	if(pthread_create(&th, NULL, routine, (void *)res))
		return (1);
	// it's not ok to use return(0) or exit(0) before join => routine is not executed
	pthread_exit(0); // в отличие от exit(0) ждет завершения тредов (т.е. выполняет routine, но не код ниже)
	if(pthread_join(th, (void **)&res))
		return (1);
	printf("Res %d\n", *res);
	free(res);
	return (0);
}