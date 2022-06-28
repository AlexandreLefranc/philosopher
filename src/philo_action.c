/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 03:35:40 by alefranc          #+#    #+#             */
/*   Updated: 2022/06/28 03:48:05 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_forks_eat(t_philo *self)
{
	if (self->id % 2 == 0)
	{
		pthread_mutex_lock(self->lfork);
		print_take_fork(self);
		pthread_mutex_lock(self->rfork);
		print_take_fork(self);
	}
	else
	{
		pthread_mutex_lock(self->rfork);
		print_take_fork(self);
		pthread_mutex_lock(self->lfork);
		print_take_fork(self);
	}
	pthread_mutex_lock(&self->sim->gmutex);
	self->nb_meal++;
	gettimeofday(&self->t_lastmeal, NULL);
	pthread_mutex_unlock(&self->sim->gmutex);
	print_eating(self);
	usleep(self->sim->input->time2eat * 1000);
	pthread_mutex_unlock(self->rfork);
	pthread_mutex_unlock(self->lfork);
	return (ERR_OK);
}

int	philo_sleep_think(t_philo *self)
{
	print_sleeping(self);
	usleep(self->sim->input->time2sleep * 1000);
	print_thinking(self);
	usleep(500);
	return (ERR_OK);
}
