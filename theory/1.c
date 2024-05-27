// Intro
// gcc -g -pthread main.c -o main

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *routine()
{
	printf("Tests from threads\n");
	sleep(3);
	printf("Ending thread\n");
	return (NULL);
}

int main()
{
	pthread_t t1, t2; //создали thread
	if(pthread_create(&t1, NULL, routine, NULL) != 0) //pointer to thread, it's attributes, pointer to the func, func's arg
		return (1);
	if(pthread_create(&t2, NULL, routine, NULL) != 0)
		return (2); 
	//then we want to terminate the process and thread's execution in the same time
	if(pthread_join(t1, NULL) != 0) //thread, **return
		return (3);
	if(pthread_join(t2, NULL) != 0)
		return (4);
	return (0);
}

/* Output:

Tests from threads
Tests from threads
Ending thread
Ending thread
*/