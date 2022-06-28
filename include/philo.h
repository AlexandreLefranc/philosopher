/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 03:40:53 by alefranc          #+#    #+#             */
/*   Updated: 2022/06/28 03:53:47 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int			init_sim(t_sim *sim, int argc, char **argv);

void		free_t_sim(t_sim *sim);
long int	time_since(struct timeval t0);
void		print_usage(void);
void		print_err(int errcode);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_atoi(const char *s);

void		print_take_fork(t_philo *self);
void		print_eating(t_philo *self);
void		print_sleeping(t_philo *self);
void		print_thinking(t_philo *self);

int			monitor_sim(t_sim *sim);

int			start_sim(t_sim *sim);

int			philo_forks_eat(t_philo *self);
int			philo_sleep_think(t_philo *self);

#endif
