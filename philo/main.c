#include "philo.h"

int	init_philos(t_all *all)
{
	int	i;

	i = 0;
	all->philos = malloc(sizeof(t_philo) * all->amount);
	if (!all->philos)
		return (1);
	while (i < all->amount)
	{
		pthread_mutex_init(&all->forks[i], 0);
		pthread_mutex_init(&all->philos[i].act, 0);
		all->philos[i].pos = i;
		all->philos[i].eatcount = 0;
		all->philos[i].eats = 0;
		all->philos[i].lfork = i;
		all->philos[i].rfork = (i + 1) % all->amount;
		all->philos[i].parent = all;
		i++;
	}
	return (0);
}

int	init_all(char **argv, t_all *all)
{
	all->amount = ft_atoi(argv[1]);
	all->tdie = ft_atoi(argv[2]);
	all->teat = ft_atoi(argv[3]);
	all->tsleep = ft_atoi(argv[4]);
	all->eat_count = ft_atoi(argv[5]);
	if (all->amount < 2 || all->amount > 200 || all->tdie < 60
		|| all->teat < 60 || all->tsleep < 60 || all->eat_count < 0)
		return (1);
	all->forks = malloc(sizeof(pthread_mutex_t) * (all->amount));
	if (!all->forks || init_philos(all))
		return (1);
	pthread_mutex_init(&all->able_write, 0);
	pthread_mutex_init(&all->dead, 0);
	pthread_mutex_lock(&all->dead);
	return (0);
}

int	start(t_all *all)
{
	pthread_t	thread;
	int			i;

	if (all->eat_count > 0)
	{
		if (pthread_create(&thread, 0, &monitoreat, all))
			return (1);
		pthread_detach(thread);
	}
	all->start = gettime();
	i = -1;
	while (++i < all->amount)
	{
		if (pthread_create(&thread, 0, &routine, &all->philos[i]))
			return (1);
		pthread_detach(thread);
		usleep(100);
	}
	return (0);
}

void	freeall(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->amount)
	{
		pthread_mutex_destroy(&all->forks[i]);
		pthread_mutex_destroy(&all->philos[i].act);
		i++;
	}
	free(all->forks);
	free(all->philos);
	pthread_mutex_destroy(&all->able_write);
	pthread_mutex_destroy(&all->dead);
}

int	main(int argc, char **argv)
{
	t_all	all;

	if (argc < 5 || argc > 6 || init_all(argv, &all))
		return (-1);
	if (start(&all))
		return (-1);
	pthread_mutex_lock(&all.dead);
	return (0);
}
