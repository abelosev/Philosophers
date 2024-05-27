// Difference between processes and threads

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>

//process
// int main()
// {
// 	int x = 2;
// 	int pid = fork();
// 	if(pid == -1)
// 		return (1);
// 	if(pid == 0)
// 		x = 3;
// 	sleep(2);
// 	if(pid != 0)
// 		wait(NULL);
// 	// printf("Process id %d\n", getpid());
// 	printf("New x %d\n", x);
// 	return (0);
// }

//threads
void *routine1(void *arg)
{
	int *x = (int *)arg;
	(*x)++;
	// sleep(2);
	printf("New x %d\n", *x);
	return (NULL);
}

void *routine2(void *arg)
{
	int *x = (int *)arg;
	sleep(2);
	printf("New x %d\n", *x);
	return (NULL);
}

int main()
{
	pthread_t t1, t2;
	int x = 2;

	if(pthread_create(&t1, NULL, routine2, &x))
		return (1);
	if(pthread_create(&t2, NULL, routine1, &x))
		return (2); 
	if(pthread_join(t1, NULL))
		return (3);
	if(pthread_join(t2, NULL))
		return (4);
	return (0);
}