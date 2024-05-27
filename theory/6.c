// Get return value from a thread (pthread_join)

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

// static int value = 0;

// void *roll_dice()
// {
// 	int x = (rand() % 6) + 1;
// 	while(x == value)
// 	{
// 		x = (rand() % 6) + 1;
// 	}
// 	printf("X %d\n", x);
// 	value = x;
// 	printf("Value %d\n", value);
// 	return (NULL);
// }

void *roll_dice()
{
	int value = (rand() % 6) + 1;
	int *returned = malloc(sizeof(int));
	if(!returned)
		return (NULL);
	*returned = value;
	printf("Address %p\n", returned);
	return ((void *)returned);
}

int main()
{
	pthread_t th;
	int *res;
	srand(time(NULL));
	// sleep(1);
	if (pthread_create(&th, NULL, roll_dice, NULL))
		return (1);
	if (pthread_join(th, (void **)&res))
		return (2);
	printf("Result from main %d\n", *res);
	printf("Address of single pointer %p\n", res);
	printf("Address of double pointer %p\n", (void **)&res);
	free(res);
	return (0);
}