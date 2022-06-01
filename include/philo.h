/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 13:15:49 by alefranc          #+#    #+#             */
/*   Updated: 2022/06/01 12:11:45 by alex             ###   ########.fr       */
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
}	t_input;

// typedef struct s_table
// {
// 	int			*forks;
// 	pthread_t	*philos;
// }	t_table;

typedef struct s_philo_id_card
{
	pthread_t		thread;
	int				id;
	struct timeval	start_existance;
	struct timeval	last_meal;
	size_t			nb_meals;
	int				*forks;
	pthread_mutex_t	*handle_fork;
	int				*running;
	t_input			*input;
}	t_philo_id_card;

// typedef struct s_thread_arg
// {
// 	int				*running;
// 	pthread_mutex_t	handle_fork;
// 	struct timeval	start_time;
// 	t_input			*input;
//
// 	size_t			id;
// 	int				*left_fork;
// 	int				*right_fork;
// 	size_t			nb_meals;
// 	struct timeval	last_meal;
// }	t_thread_arg;

// parse.c
int	parse_input(t_input *input, int argc, char **argv);

// forks.c
pthread_mutex_t	*init_forks(int nb_philo);
int	destroy_forks(pthread_mutex_t **forks, int nb_philo);

// philo.c
pthread_t	*init_philos(t_input *input);
int		destroy_philos(pthread_t **philos);

// debug.c
void	print_philo(t_philo_id_card *philo);
void	print_input(t_input *input);


#endif
