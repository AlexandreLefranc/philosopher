/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 13:18:35 by alefranc          #+#    #+#             */
/*   Updated: 2022/06/12 13:27:28 by alex             ###   ########.fr       */
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
	// pthread_mutex_lock(id_card->handle_fork);
	printf("Hello philo nb %d\n", id_card->id);
	// pthread_mutex_unlock(id_card->handle_fork);
	return (NULL);
}

// static void
// start_sim(t_input *input, int *forks, t_philo_id_card *philo, pthread_mutex_t *handle_fork)
// {
// 	int	i;
// 	int	running;
//
// 	running = 1;
// 	i = 0;
// 	while (i < input->nb_philo)
// 	{
// 		philo[i].id = i + 1;
// 		gettimeofday(&(philo[i].start_existance), NULL);
// 		philo[i].last_meal = philo[i].start_existance;
// 		philo[i].nb_meals = 0;
// 		philo[i].forks = forks;
// 		philo[i].handle_fork = handle_fork;
// 		philo[i].running = &running;
// 		philo[i].input = input;
// 		pthread_create(&(philo[i].thread), NULL, &routine, philo + i);
// 		usleep(1);
// 		i++;
// 	}
// }

int	main(int argc, char **argv)
{
	t_sim	sim;

	sim.running = 1;
	if (parse_input(&(sim.input), argc, argv) != 0)
		return (1);
	sim.forks = calloc(sizeof(*(sim.forks)), sim.input.nb_philo);
	pthread_mutex_init(&(sim.handle_fork), NULL);
	// forks = calloc(sizeof(*forks), input.nb_philo);
	// philo = calloc(sizeof(*philo), input.nb_philo);
	//
	// pthread_mutex_init(&handle_fork, NULL);
	// start_sim(&input, forks, philo, &handle_fork);
	print_t_sim(sim);

	// print_philo(philo);
	// free(sim.forks);
	// free(philo);

	return (0);
}
