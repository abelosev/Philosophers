#include "../inc/philo.h"

int		ft_atoi(const char *str)
{
	int					i;
	int					sign;
	long long int		res;   // ???

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] <= 13 && str[0] >= 9) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (sign * res);
}