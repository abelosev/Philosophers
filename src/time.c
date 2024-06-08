// #include "philo.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/time.h>

// long int : Диапазон значений зависит от платформы. На 32-битных системах он может представлять значения от -2,147,483,648 до 2,147,483,647, а на 64-битных — от -9,223,372,036,854,775,808 до 9,223,372,036,854,775,807.

u_int64_t get_timestamp()
{
	struct timeval tv;
	u_int64_t time_ms;

	gettimeofday(&tv, NULL);
	time_ms = tv.tv_sec * 1000 + (tv.tv_usec / 1000);
	return (time_ms);
}

// int main()
// {
// 	u_int64_t start;
// 	u_int64_t end;
// 	start = get_timestamp();
// 	usleep(500000);
// 	end = get_timestamp();
// 	printf("%llu\n", end - start);
// 	return (0);
// }

//ft_usleep : переписать так, чтобы "спать" короткими интервалами и проверять условие death of a philosopher

