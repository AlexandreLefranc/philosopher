/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 13:18:35 by alefranc          #+#    #+#             */
/*   Updated: 2022/06/13 16:30:16 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void	*routine(void *arg)
// {
// 	t_philo_id_card *id_card;
//
// 	id_card = (t_philo_id_card *)arg;
// 	pthread_mutex_lock(id_card->handle_fork);
// 	printf("Hello philo nb %d\n", id_card->id);
// 	*id_card->running = *id_card->running + 1;
// 	*id_card->lfork = *id_card->lfork + 1;
// 	*id_card->rfork = *id_card->rfork + 1;
// 	printf("From philo%d: running = %d (%p)\n", id_card->id, *id_card->running, id_card->running);
// 	printf("From philo%d: lfork = %p (%d)\n\n", id_card->id, id_card->lfork, *id_card->lfork);
// 	pthread_mutex_unlock(id_card->handle_fork);
// 	return (NULL);
// }

static long int    diff_time_in_msec(struct timeval t1, struct timeval t2)
{
	long int diff;

	diff = 0;
	diff += (t1.tv_sec - t2.tv_sec) * 1000;
	diff += (t1.tv_usec - t2.tv_usec) / 1000;
	return (diff);
}

static void	print_taking_fork(t_philo_id_card *id_card)
{
	struct timeval	now;
	long int	diff;

	gettimeofday(&now, NULL);
	diff = diff_time_in_msec(now, id_card->start_existance);
	if (*id_card->running == 1)
		printf("%ld ms %d had taken a fork\n", diff, id_card->id);
}

static void	print_eating(t_philo_id_card *id_card)
{
	struct timeval	now;
	long int	diff;

	gettimeofday(&now, NULL);
	diff = diff_time_in_msec(now, id_card->start_existance);
	if (*id_card->running == 1)
		printf("%ld ms %d is eating\n", diff, id_card->id);
}

static void	print_sleeping(t_philo_id_card *id_card)
{
	struct timeval	now;
	long int	diff;

	gettimeofday(&now, NULL);
	diff = diff_time_in_msec(now, id_card->start_existance);
	if (*id_card->running == 1)
		printf("%ld ms %d is sleeping\n", diff, id_card->id);
}

static void	print_thinking(t_philo_id_card *id_card)
{
	struct timeval	now;
	long int	diff;

	gettimeofday(&now, NULL);
	diff = diff_time_in_msec(now, id_card->start_existance);
	if (*id_card->running == 1)
		printf("%ld ms %d is thinking\n", diff, id_card->id);
}

static void	*routine(void *arg)
{
	t_philo_id_card	*id_card;

	id_card = (t_philo_id_card *)arg;
	while (*(id_card->running) == 1 && (id_card->input->nb_meal_max == -1
			|| id_card->nb_meals < id_card->input->nb_meal_max))
	{
		if (*id_card->lfork == FREE && *id_card->rfork == FREE
			&& id_card->lfork != id_card->rfork)
		{
			pthread_mutex_lock(id_card->handle_fork);
			if (*id_card->lfork == FREE && *id_card->rfork == FREE)
			{
				*id_card->lfork = USED;
				print_taking_fork(id_card);
				*id_card->rfork = USED;
				print_taking_fork(id_card);
				pthread_mutex_unlock(id_card->handle_fork);
			}
			else
			{
				pthread_mutex_unlock(id_card->handle_fork);
				continue ;
			}
			gettimeofday(&id_card->last_meal, NULL);
			id_card->nb_meals++;
			print_eating(id_card);
			usleep(id_card->input->time2eat * 1000);
			*id_card->lfork = FREE;
			*id_card->rfork = FREE;
			print_sleeping(id_card);
			usleep(id_card->input->time2sleep * 1000);
			print_thinking(id_card);
		}
	}
	return (NULL);
}

static int	launch_sim(t_sim *sim)
{
	int		i;

	i = 0;
	while (i < sim->input.nb_philo)
	{
		sim->philo[i].id = i + 1;
		gettimeofday(&(sim->philo[i].start_existance), NULL);
		sim->philo[i].last_meal = sim->philo[i].start_existance;
		sim->philo[i].nb_meals = 0;
		sim->philo[i].lfork = sim->forks + i;
		sim->philo[i].rfork = sim->forks + ((i + 1) % sim->input.nb_philo);
		sim->philo[i].handle_fork = &sim->handle_fork;
		sim->philo[i].running = &sim->running;
		sim->philo[i].input = &sim->input;
		pthread_create(&sim->philo[i].thread, NULL, &routine, sim->philo + i);
		i++;
	}
	return (0);
}

static int	is_dead(t_philo_id_card *id_card)
{
	long int	diff;
	struct timeval	now;

	gettimeofday(&now, NULL);
	diff = diff_time_in_msec(now, id_card->last_meal);
	if (diff > id_card->input->time2die)
	{
		diff = diff_time_in_msec(now, id_card->start_existance);
		printf("%ld ms %d died\n", diff, id_card->id);
		return (1);
	}
	return (0);
}

static int	supervise_sim(t_sim *sim)
{
	int	stop_sim;
	int	i;

	stop_sim = 0;
	while (1)
	{
		i = 0;
		while (i < sim->input.nb_philo)
		{
			if (is_dead(sim->philo + i) == 1)
			{
				stop_sim = 1;
				break;
			}
			i++;
		}
		if (stop_sim == 1)
			break;
	}
	sim->running = 0;
	i = 0;
	while (i < sim->input.nb_philo)
	{
		pthread_detach(sim->philo[i].thread);
		i++;
	}
	usleep((sim->input.time2eat + sim->input.time2sleep + 10) * 1000);
	return (1);
}

int	main(int argc, char **argv)
{
	t_sim	*sim;

	sim = calloc(sizeof(*sim), 1);
	if (sim == NULL)
		return (1);
	sim->running = 1;
	if (parse_input(&(sim->input), argc, argv) != 0)
		return (free(sim), 1);
	if (pthread_mutex_init(&(sim->handle_fork), NULL) != 0)
		return (free(sim), 1);
	sim->forks = calloc(sizeof(*(sim->forks)), sim->input.nb_philo);
	if (sim->forks == NULL)
		return (1);
	sim->philo = calloc(sizeof(*(sim->philo)), sim->input.nb_philo);
	if (sim->philo == NULL)
		return (free(sim->forks), free(sim), 1);

	launch_sim(sim);

	supervise_sim(sim);
	// print_t_sim(*sim);

	free(sim->forks);
	free(sim->philo);
	free(sim);

	return (0);
}
