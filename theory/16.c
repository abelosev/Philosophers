// What is pthread_t?

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/syscall.h> //for gettid()

#define THREAD_NUM 2

void *routine(void *arg)
{
	pthread_t th = pthread_self();
	printf("%lu\n", (unsigned long) th);
	return (NULL);
	//syscall(SYS__gettid) is deprecated
}

int main()
{
	pthread_t th[THREAD_NUM];
	int i;

	i = 0;
	while(i < THREAD_NUM)
	{
		if(pthread_create(&th[i], NULL, routine, NULL))
			return 1;
		// printf("p_thread[%d] : %u\n", i, th[i]);
		i++;
	}
	i = 0;
	while(i < THREAD_NUM)
	{
		if(pthread_join(th[i], NULL))
			return 1;
		i++;
	}
	return 0;
}