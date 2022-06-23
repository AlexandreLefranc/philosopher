/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:17:33 by alefranc          #+#    #+#             */
/*   Updated: 2022/06/23 13:48:31 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo2.h"

static long int	get_time_since(struct timeval t0)
{
	long int		diff;
	struct timeval	t1;

	if (gettimeofday(&t1, NULL) != 0)
		return (-1);
	diff = 0;
	diff += (t1.tv_sec - t0.tv_sec) * 1000;
	diff += (t1.tv_usec - t0.tv_usec) / 1000;
	return (diff);
}

static void	free_t_sim(t_sim *sim)
{
	free(sim->input);
	free(sim->forks);
	free(sim->philos);
	free(sim);
}

static int	try_eat(t_philo *self)
{
	t_fork	*lfork;
	t_fork	*rfork;

	lfork = self->sim->forks + (self->id - 1) % self->sim->input->nb_philo;
	rfork = self->sim->forks + (self->id - 0) % self->sim->input->nb_philo;
	if (lfork->state == AVAIL && rfork->state == AVAIL)
	{
		lfork->state = TAKEN;
		pthread_mutex_lock(&lfork->mutex);
		printf("%ld %d has taken a fork\n", get_time_since(self->sim->t0), self->id);
		rfork->state = TAKEN;
		pthread_mutex_lock(&rfork->mutex);
		printf("%ld %d has taken a fork\n", get_time_since(self->sim->t0), self->id);
		gettimeofday(&self->t_lastchange, NULL);
		gettimeofday(&self->t_lastmeal, NULL);
		self->nb_meals++;
		self->state = EATING;
		printf("%ld %d is eating\n", get_time_since(self->sim->t0), self->id);
	}
	return (ERR_OK);
}

static int	try_sleep(t_philo *self)
{
	t_fork	*lfork;
	t_fork	*rfork;

	lfork = self->sim->forks + (self->id - 1) % self->sim->input->nb_philo;
	rfork = self->sim->forks + (self->id - 0) % self->sim->input->nb_philo;
	if (get_time_since(self->t_lastchange) > self->sim->input->time2eat)
	{
		lfork->state = AVAIL;
		pthread_mutex_unlock(&lfork->mutex);
		rfork->state = AVAIL;
		pthread_mutex_unlock(&rfork->mutex);
		gettimeofday(&self->t_lastchange, NULL);
		self->state = SLEEPING;
		printf("%ld %d is sleeping\n", get_time_since(self->sim->t0), self->id);
	}
	return (ERR_OK);
}

static int	try_think(t_philo *self)
{
	if (get_time_since(self->t_lastchange) > self->sim->input->time2sleep)
	{
		gettimeofday(&self->t_lastchange, NULL);
		self->state = THINKING;
		printf("%ld %d is thinking\n", get_time_since(self->sim->t0), self->id);
	}
	return (ERR_OK);
}

static int	clean_thread(t_philo *self)
{
	t_fork	*lfork;
	t_fork	*rfork;

	lfork = self->sim->forks + (self->id - 1) % self->sim->input->nb_philo;
	rfork = self->sim->forks + (self->id - 0) % self->sim->input->nb_philo;
	if (self->state == EATING)
	{
		pthread_mutex_unlock(&lfork->mutex);
		pthread_mutex_unlock(&rfork->mutex);
	}
	self->state = DONE;
	return (ERR_OK);
}

static int	try_change_state(t_philo *self)
{
	if (self->sim->any_death != 0)
		clean_thread(self);
	else if (is_dead(self) == 1)
		self->state = DEAD;
	else if (self->state == THINKING &&
			 self->sim->input->nb_meal_max > 0 &&
			 self->nb_meals >= self->sim->input->nb_meal_max)
		self->state = DONE;
	else if (self->state == THINKING)
		try_eat(self);
	else if (self->state == EATING)
		try_sleep(self);
	else if (self->state == SLEEPING)
		try_think(self);
	return (ERR_OK);
}

static void	*life(void *arg)
{
	t_philo	*self;

	self = arg;
	while (self->state != DEAD && self->state != DONE)
	{
		pthread_mutex_lock(&self->sim->mutex);
		try_change_state(self);
		pthread_mutex_unlock(&self->sim->mutex);
		usleep(500);
	}
	return (NULL);
}

static int	start_sim(t_sim *sim)
{
	int	errcode;
	int	i;

	if (pthread_mutex_init(&sim->mutex, NULL) != 0)
		return (ERR_MUTEX);
	errcode = gettimeofday(&sim->t0, NULL);
	if (errcode != 0)
		return (ERR_TIME);
	i = 0;
	while (i < sim->input->nb_philo)
	{
		sim->philos[i].t_lastchange = sim->t0;
		sim->philos[i].t_lastmeal = sim->t0;
		errcode = pthread_create(&sim->philos[i].thread, NULL, life, sim->philos + i);
		i++;
	}
	return (ERR_OK);
}

int	main(int argc, char **argv)
{
	t_sim	*sim;
	int		errcode;

	sim = calloc(sizeof(*sim), 1);
	if (sim == NULL)
		return (ERR_MALLOC);
	errcode = init_sim(sim, argc, argv);
	if (errcode != ERR_OK)
		return (free_t_sim(sim), print_err(errcode), errcode);
	start_sim(sim);
	monitor_sim(sim);
	free_t_sim(sim);
	return (0);
}
