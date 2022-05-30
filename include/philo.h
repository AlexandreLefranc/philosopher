/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 13:15:49 by alefranc          #+#    #+#             */
/*   Updated: 2022/05/30 22:41:51 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# include <stdio.h>

enum e_fork_state
{
	FREE,
	USED
};

typedef struct s_input
{
	int	nb_philo;
	int	time2die;
	int	time2eat;
	int	time2sleep;
	int	nb_meal_max;

	int	running;
	struct timeval	*start;
}	t_input;

typedef struct s_routine_arg
{
	t_input	*input;
	int		id;
}	t_routine_arg;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	lfork;
	pthread_mutex_t	rfork;
	int				id;

}	t_philo;

// parse.c
int	parse_input(t_input *input, int argc, char **argv);

// forks.c
pthread_mutex_t	*init_forks(int nb_philo);
int	destroy_forks(pthread_mutex_t **forks, int nb_philo);

// philo.c
pthread_t	*init_philos(t_input *input);
int		destroy_philos(pthread_t **philos);

#endif
