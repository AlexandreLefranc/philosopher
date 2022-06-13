/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 13:18:35 by alefranc          #+#    #+#             */
/*   Updated: 2022/06/13 12:55:20 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void	free_t_table(t_table *table)
// {
// 	free(table->forks);
// 	free(table->philos);
// }
//
// static int	init_t_table(t_table *table, t_input input)
// {
// 	table->forks = calloc(sizeof(*table->forks), input.nb_philo);
// 	if (table->forks == NULL)
// 		return (1);
// 	table->philos = calloc(sizeof(*table->philos), input.nb_philo);
// 	if (table->philos == NULL)
// 		return (free(table->forks), 1);
// 	return (0);
// }

// static t_thread_arg	*start_sim(t_input input, t_table table)
// {
//
// }

void	*routine(void *arg)
{
	t_philo_id_card *id_card;

	id_card = (t_philo_id_card *)arg;
	pthread_mutex_lock(id_card->handle_fork);
	printf("Hello philo nb %d\n", id_card->id);
	*(id_card->running) = 0;
	*(id_card->lfork) = *(id_card->lfork) + 1;
	*(id_card->rfork) = *(id_card->rfork) + 1;
	printf("From philo%d: running = %d\n", id_card->id, *id_card->running);
	printf("From philo%d: lfork = %p (%d)\n\n", id_card->id, id_card->lfork, *id_card->lfork);
	pthread_mutex_unlock(id_card->handle_fork);
	return (NULL);
}

static int launch_sim(t_sim sim)
{
	int	i;

	i = 0;
	while (i < sim.input.nb_philo)
	{
		sim.philo[i].id = i + 1;
		gettimeofday(&(sim.philo[i].start_existance), NULL);
		sim.philo[i].last_meal = sim.philo[i].start_existance;
		sim.philo[i].nb_meals = 0;
		sim.philo[i].lfork = sim.forks + i;
		sim.philo[i].rfork = sim.forks + ((i + 1) % sim.input.nb_philo);
		sim.philo[i].handle_fork = &sim.handle_fork;
		sim.philo[i].running = &sim.running;
		sim.philo[i].input = &sim.input;
		pthread_create(&sim.philo[i].thread, NULL, &routine, sim.philo + i);
		usleep(100000);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_sim	sim;

	sim.running = 1;
	if (parse_input(&(sim.input), argc, argv) != 0)
		return (1);
	if (pthread_mutex_init(&(sim.handle_fork), NULL) != 0)
		return (1);
	sim.forks = calloc(sizeof(*(sim.forks)), sim.input.nb_philo);
	if (sim.forks == NULL)
		return (1);
	sim.philo = calloc(sizeof(*(sim.philo)), sim.input.nb_philo);
	if (sim.philo == NULL)
		return (free(sim.forks), 1);

	launch_sim(sim);
	// pthread_mutex_init(&handle_fork, NULL);
	// start_sim(&input, forks, philo, &handle_fork);
	sleep(1);
	print_t_sim(sim);
	printf("%d\n", sim.running);

	free(sim.forks);
	free(sim.philo);

	return (0);
}
