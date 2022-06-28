/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 03:35:48 by alefranc          #+#    #+#             */
/*   Updated: 2022/06/28 03:48:15 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_take_fork(t_philo *self)
{
	pthread_mutex_lock(&self->sim->gmutex);
	if (self->sim->any_death == 0)
		printf("\033[33m%ld %d has taken a fork\033[0m\n",
			time_since(self->sim->t0), self->id + 1);
	pthread_mutex_unlock(&self->sim->gmutex);
}

void	print_eating(t_philo *self)
{
	pthread_mutex_lock(&self->sim->gmutex);
	if (self->sim->any_death == 0)
		printf("\033[32m%ld %d is eating\033[0m\n",
			time_since(self->sim->t0), self->id + 1);
	pthread_mutex_unlock(&self->sim->gmutex);
}

void	print_sleeping(t_philo *self)
{
	pthread_mutex_lock(&self->sim->gmutex);
	if (self->sim->any_death == 0)
		printf("\033[35m%ld %d is sleeping\033[0m\n",
			time_since(self->sim->t0), self->id + 1);
	pthread_mutex_unlock(&self->sim->gmutex);
}

void	print_thinking(t_philo *self)
{
	pthread_mutex_lock(&self->sim->gmutex);
	if (self->sim->any_death == 0)
		printf("\033[36m%ld %d is thinking\033[0m\n",
			time_since(self->sim->t0), self->id + 1);
	pthread_mutex_unlock(&self->sim->gmutex);
}
