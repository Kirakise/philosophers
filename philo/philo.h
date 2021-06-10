#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdint.h>

struct s_all;

typedef struct s_philo{
    int pos;
    int eats;
    unsigned long long  lifetime;
    unsigned long long  leat;
    int lfork;
    int rfork;
    int eatcount;
    struct s_all *parent;
    pthread_mutex_t act;

}               t_philo;

typedef struct s_all{
    int amount;
    unsigned long long int tdie;
    unsigned long long int teat;
    unsigned long long int tsleep;
    int eat_count;
    unsigned long long int start;
    t_philo *philos;
    pthread_mutex_t *forks;
    pthread_mutex_t able_write;
    pthread_mutex_t	dead;
}               t_all;

int ft_atoi(char *s);
unsigned long long gettime(void);
void writemsg(t_philo *ph, int type);
void *routine(void *arg);
void *monitor(void *arg);
void *monitoreat(void *arg);
#endif