//What are Race Conditions?

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>

//use this to compile: gcc -S 3.c

int mails = 0;

void *routine()
{
	int i;
	while(i < 1000000)
	{
		mails++;
		i++;
	}
	return (NULL);
	//read mails
	//increment
	//write mails
}

void *routine2()
{
	int i;
	sleep(3); //временное решение проблемы race conditions
	while(i < 1000000)
	{
		mails++;
		i++;
	}
	return (NULL);
	//read mails
	//increment
	//write mails
}

int main()
{
	pthread_t t1, t2;

	if (pthread_create(&t1, NULL, routine, NULL))
		return (1);
	if (pthread_create(&t2, NULL, routine2, NULL))
		return (2);
	if (pthread_join(t1, NULL))
		return (3);
	if (pthread_join(t2, NULL))
		return (4);
	printf("Mails nb : %d\n", mails);
	return (0);
}