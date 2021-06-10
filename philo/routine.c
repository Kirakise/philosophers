#include "philo.h"

void *monitor(void *arg)
{
    t_philo *philo;

    philo = arg;
    while (1)
    {
        pthread_mutex_lock(&philo->act);
        if (!philo->eats && gettime() > philo->lifetime)
        {
            writemsg(philo, 0);
            pthread_mutex_unlock(&philo->parent->dead);
            return (0);
        }
        pthread_mutex_unlock(&philo->act);
        usleep(100);
    }
}

void *monitoreat(void *arg)
{
    int i;
    t_all *all;

    all = arg;
    while (1)
    {
        i = 0;
        while (i < all->amount)
        {
            if (all->philos[i].eatcount < all->eat_count)
                break ;
            i++;
        }
        if (i == all->amount)
        {
            writemsg(&all->philos[0], 4);
            pthread_mutex_lock(&all->able_write);
            pthread_mutex_unlock(&all->dead);
            return 0;
        }
        usleep(100);
    }
}

void eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->parent->forks[philo->lfork]);
    writemsg(philo, 5);
    pthread_mutex_lock(&philo->parent->forks[philo->rfork]);
    writemsg(philo, 5);
    philo->leat = gettime();
    philo->lifetime = philo->leat + philo->parent->tdie;
    writemsg(philo, 1);
    usleep(philo->parent->teat * 1000);
    philo->eatcount++;
    pthread_mutex_unlock(&philo->parent->forks[philo->lfork]);
    pthread_mutex_unlock(&philo->parent->forks[philo->rfork]);
    writemsg(philo, 2);
    usleep(philo->parent->tsleep * 1000);
    writemsg(philo, 3);
}

void *routine(void *arg)
{
    t_philo *philo;
    pthread_t id;

    philo = arg;
    philo->leat = gettime();
    philo->lifetime = philo->leat + philo->parent->tdie;
    if (pthread_create(&id, 0, &monitor, arg))
        return ((void *)1);
    pthread_detach(id);
    while (1)
        eat(philo);
    return (0);
}