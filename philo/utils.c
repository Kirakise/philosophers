#include "philo.h"

int	ft_atoi(char *s)
{
	int			znak;
	long long	res;
	int			i;

	res = 0;
	if (!s)
		return (0);
	i = 0;
	if (s[i] == '-' && ++i)
		znak = 1;
	else
		znak = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		res = res * 10 + s[i++] - '0';
	}
	if (znak || res > INT32_MAX)
		return (-res);
	else
		return (res);
}

unsigned long long	gettime(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, 0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
