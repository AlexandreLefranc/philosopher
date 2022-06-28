/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 03:35:53 by alefranc          #+#    #+#             */
/*   Updated: 2022/06/28 03:52:39 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	parse_input(t_sim *sim, int argc, char **argv)
{
	t_input	*input;

	if (argc != 5 && argc != 6)
		return (ERR_ARG);
	input = malloc(sizeof(*input) * 1);
	if (input == NULL)
		return (ERR_MALLOC);
	input->nb_philo = ft_atoi(argv[1]);
	input->time2die = ft_atoi(argv[2]);
	input->time2eat = ft_atoi(argv[3]);
	input->time2sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		input->nb_meal_max = ft_atoi(argv[5]);
	else
		input->nb_meal_max = -1;
	sim->input = input;
	return (ERR_OK);
}

static int	check_input(t_sim *sim)
{
	if (sim->input->nb_philo < 1)
		return (ERR_ARG);
	if (sim->input->time2die < 1)
		return (ERR_ARG);
	if (sim->input->time2eat < 1)
		return (ERR_ARG);
	if (sim->input->time2sleep < 1)
		return (ERR_ARG);
	if (sim->input->nb_meal_max < -1)
		return (ERR_ARG);
	return (ERR_OK);
}

static int	init_forks(t_sim *sim)
{
	int	i;

	sim->forks = malloc(sizeof(*sim->forks) * sim->input->nb_philo);
	if (sim->forks == NULL)
		return (ERR_MALLOC);
	i = 0;
	while (i < sim->input->nb_philo)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
			return (ERR_MUTEX);
		i++;
	}
	return (ERR_OK);
}

static int	init_philo(t_sim *sim)
{
	int	i;

	sim->philos = malloc(sizeof(*sim->philos) * sim->input->nb_philo);
	if (sim->philos == NULL)
		return (ERR_MALLOC);
	i = 0;
	while (i < sim->input->nb_philo)
	{
		sim->philos[i].id = i;
		sim->philos[i].lfork = sim->forks + ((i + 0) % sim->input->nb_philo);
		sim->philos[i].rfork = sim->forks + ((i + 1) % sim->input->nb_philo);
		sim->philos[i].nb_meal = 0;
		sim->philos[i].sim = sim;
		i++;
	}
	return (ERR_OK);
}

int	init_sim(t_sim *sim, int argc, char **argv)
{
	int	errcode;

	errcode = parse_input(sim, argc, argv);
	if (errcode != ERR_OK)
		return (errcode);
	errcode = check_input(sim);
	if (errcode != ERR_OK)
		return (errcode);
	errcode = init_forks(sim);
	if (errcode != ERR_OK)
		return (errcode);
	errcode = init_philo(sim);
	if (errcode != ERR_OK)
		return (errcode);
	sim->any_death = 0;
	if (gettimeofday(&sim->t0, NULL) != 0)
		return (ERR_TIME);
	if (pthread_mutex_init(&sim->gmutex, NULL) != 0)
		return (ERR_MUTEX);
	return (ERR_OK);
}
