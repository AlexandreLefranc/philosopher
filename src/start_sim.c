/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 03:35:42 by alefranc          #+#    #+#             */
/*   Updated: 2022/06/28 03:48:08 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	life_keep_going(t_philo *self)
{
	int	ret;

	pthread_mutex_lock(&self->sim->gmutex);
	if (self->nb_meal != self->sim->input->nb_meal_max
		&& self->sim->any_death == 0)
		ret = 1;
	else
		ret = 0;
	pthread_mutex_unlock(&self->sim->gmutex);
	return (ret);
}

static void	*life(void *arg)
{
	t_philo	*self;

	self = arg;
	if (self->id % 2 == 0)
		usleep(100);
	if (self->sim->input->nb_philo == 1)
	{
		print_take_fork(self);
		usleep((self->sim->input->time2die + 5) * 1000);
	}
	while (life_keep_going(self) == 1)
	{
		philo_forks_eat(self);
		philo_sleep_think(self);
	}
	return (NULL);
}

int	start_sim(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->input->nb_philo)
	{
		sim->philos[i].t_lastmeal = sim->t0;
		pthread_create(&sim->philos[i].thread, NULL, life, sim->philos + i);
		i++;
	}
	return (ERR_OK);
}
