// What are detached threads?

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

#define THREAD_NUM 2

void *routine(void *arg)
{
	sleep(1);
	printf("Finished\n");
	return(NULL);
}

int main()
{
	pthread_t th[THREAD_NUM];
	pthread_attr_t detachedThread;
	pthread_attr_init(&detachedThread);
	pthread_attr_setdetachstate(&detachedThread, PTHREAD_CREATE_DETACHED);
	int i;

	i = 0;
	while(i < THREAD_NUM)
	{
		if(pthread_create(&th[i], &detachedThread, routine, NULL) != 0)
			perror("Failed to create a thread\n");
		// pthread_detach(th[i]);
		i++;
	}
	i = 0;
	// while(i < THREAD_NUM)
	// {
	// 	if(pthread_join(th[i], NULL) != 0)
	// 		perror("Failed to join a thread\n");
	// 	i++;
	// }
	pthread_attr_destroy(&detachedThread);
	pthread_exit(0); //если оставить return(0), то работать не будет !
}