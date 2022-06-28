#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>

enum e_errors
{
	ERR_OK = 0,
	ERR_MALLOC,
	ERR_ARG,
	ERR_MUTEX,
	ERR_TIME
};

typedef struct s_input
{
	int	nb_philo;
	int	time2die;
	int	time2eat;
	int	time2sleep;
	int	nb_meal_max;
}	t_input;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	struct timeval	t_lastmeal;
	int				nb_meal;
	struct s_sim	*sim;
}	t_philo;

typedef struct s_sim
{
	int				any_death;
	struct timeval	t0;
	pthread_mutex_t	gmutex;
	pthread_mutex_t	*forks;
	t_input			*input;
	t_philo			*philos;
}	t_sim;

#endif
