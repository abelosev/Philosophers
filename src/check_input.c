#include "../inc/philo.h"

bool is_digit(char c)
{
	if(!(c >= '0' && c <= '9'))
		return (false);
	return (true);
}

bool check_nbr(const char *str, int *res)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	else if(str[i] == '-')
		return (false);
	if(str[i] == '0' && str[i + 1])
		return (false);
	while (str[i])
	{
		if(!is_digit(str[i]))
			return (false);
		*res = *res * 10 + str[i] - '0';
		if(*res > 2147483647 || *res < 0)
			return (false);
		i++;
	}
	return (true);
}

bool check_input(int ac, char **av)
{
	int i;
	int res;

	i = 1;
	res = 0;
	if(ac < 5 || ac > 6)
	{
		printf("The number of args is not correct\n");
		return (false);
	}
	while(i < ac)
	{
		if(!check_nbr(av[i], &res))
		{
			printf("At least one of the args is not correct\n");
			return (false);
		}
		if(i == 1 && res > 200)
		{
			printf("The nb of philos should be less than 200\n");
			return (false);
		}
		if(i != 5 && res == 0)
		{
			printf("This args can't be equal to '0'\n");
			return (false);
		}
		if(i >= 2 && i <= 4 && res < 60)
		{
			printf("The value is lower than 60 ms\n");
			return (false);
		}
		res = 0;
		i++;
	}
	return (true);
}