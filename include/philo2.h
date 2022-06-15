/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:16:38 by alefranc          #+#    #+#             */
/*   Updated: 2022/06/16 15:24:28 by alefranc         ###   ########.fr       */
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
	ERR_MUTEX
};

enum e_fork_state
{
	AVAIL,
	TAKEN
};

enum e_philo_state
{
	DEAD,
	DONE,
	EATING,
	SLEEPING,
	THINKING
};

typedef struct s_input
{
	int	nb_philo;
	int	time2die;
	int	time2eat;
	int	time2sleep;
	int	nb_meal_max;
}	t_input;

typedef struct s_fork
{
	int				state;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philo
{
	int				id;
	int				state;
	pthread_t		thread;
	struct timeval	start_existance;
	struct timeval	last_meal;
	int				nb_meals;

	struct s_sim	*sim;
}	t_philo;

typedef struct s_sim
{
	int		running;
	t_input	*input;
	t_fork	*forks;
	t_philo	*philos;
}	t_sim;

#endif