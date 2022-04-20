/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 13:15:49 by alefranc          #+#    #+#             */
/*   Updated: 2022/04/20 12:52:03 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# include <stdio.h>

// typedef struct s_sim
// {
// 	int		running;
// 	t_dlst	philo;
// }	t_sim;

typedef struct s_input
{
	int	nb_philo;
	int	time2die;
	int	time2eat;
	int	time2sleep;
}	t_input;

// parse.c
int	parse_input(t_input *input, int argc, char **argv);

// forks.c
pthread_mutex_t	*init_forks(int nb_philo);
int	destroy_forks(pthread_mutex_t **forks, int nb_philo);

// philo.c
pthread_t	*init_philos(t_input	*input);

#endif
