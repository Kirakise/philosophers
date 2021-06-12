#include "philo.h"

char	*getmsg(int type)
{
	if (type == 1)
		return (" is eating\n");
	else if (type == 2)
		return (" is sleeping\n");
	else if (type == 3)
		return (" is thinking\n");
	else if (type == 4)
		return ("must eat count reached\n");
	else if (type == 5)
		return (" taken fork");
	return (" is dead\n");
}

void	writemsg(t_philo *ph, int type)
{
	pthread_mutex_lock(&ph->parent->able_write);
	printf("%llu\t", gettime() - ph->parent->start);
	if (type != 4)
		printf("%d", ph->pos + 1);
	printf("%s\n", getmsg(type));
	pthread_mutex_unlock(&ph->parent->able_write);
}
