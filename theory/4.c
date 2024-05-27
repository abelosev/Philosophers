//What is a mutex in C? (pthread_mutex)

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t mutex;

void *routine()
{
	int i;
	pthread_mutex_lock(&mutex);
	while(i < 100000)
	{
		mails++;
		i++;
	}
	pthread_mutex_unlock(&mutex);
	return (NULL);
}

int main()
{
	pthread_t t1, t2;
	pthread_mutex_init(&mutex, NULL);

	if (pthread_create(&t1, NULL, routine, NULL))
		return (1);
	if (pthread_create(&t2, NULL, routine, NULL))
		return (2);
	if (pthread_join(t1, NULL))
		return (3);
	if (pthread_join(t2, NULL))
		return (4);
	printf("Mails nb : %d\n", mails);
	pthread_mutex_destroy(&mutex);
	return (0);
}