/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 03:35:44 by alefranc          #+#    #+#             */
/*   Updated: 2022/06/28 03:48:12 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	any_death(t_sim *sim)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&sim->gmutex);
	while (i < sim->input->nb_philo)
	{
		if (time_since(sim->philos[i].t_lastmeal) >= sim->input->time2die
			&& sim->philos[i].nb_meal != sim->input->nb_meal_max)
		{
			printf("\033[31m%ld %d died\033[0m\n", time_since(sim->t0), i + 1);
			pthread_mutex_unlock(&sim->gmutex);
			return (1);
		}
		i++;
	}
	pthread_mutex_unlock(&sim->gmutex);
	return (0);
}

static int	all_done(t_sim *sim)
{
	int	i;
	int	nb_done;
	int	all_done;

	nb_done = 0;
	i = 0;
	pthread_mutex_lock(&sim->gmutex);
	while (i < sim->input->nb_philo)
	{
		if (sim->philos[i].nb_meal == sim->input->nb_meal_max)
			nb_done++;
		i++;
	}
	if (nb_done == sim->input->nb_philo)
		all_done = 1;
	else
		all_done = 0;
	pthread_mutex_unlock(&sim->gmutex);
	return (all_done);
}

int	monitor_sim(t_sim *sim)
{
	while (1)
	{
		if (any_death(sim) == 1)
		{
			pthread_mutex_lock(&sim->gmutex);
			sim->any_death = 1;
			pthread_mutex_unlock(&sim->gmutex);
			break ;
		}
		if (all_done(sim) == 1)
			break ;
		usleep(1000);
	}
	return (ERR_OK);
}
