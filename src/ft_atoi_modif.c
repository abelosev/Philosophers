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

int ft_atoi_modif(const char *str)
{
	int		i;
	int		res;

	i = 0;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res);
}