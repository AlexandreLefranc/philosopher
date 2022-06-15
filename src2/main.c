/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:17:33 by alefranc          #+#    #+#             */
/*   Updated: 2022/06/16 15:19:56 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo2.h"

static void	print_usage()
{
	printf("Usage:\n");
	printf("  ./philo <nb_philo> <time2die> <time2eat> <time2sleep>\
	[<nb_meal>]\n");
	printf("nb_philo: Number of philosopher. Must be more than 1.\n");
	printf("time2die: Time before a philosopher dies from starvation (ms).\n");
	printf("time2eat: Time a philosopher takes to eat (ms).\n");
	printf("time2sleep: Time a philosopher takes to sleep (ms).\n");
	printf("nb_meal: Number of time each philosopher must eat.\n");
}

static void	print_err(int errcode)
{
	if (errcode == ERR_ARG)
	{
		printf("Error! Invalid arguments!\n");
		print_usage();
	}
	if (errcode == ERR_MALLOC)
		printf("Error! A malloc() failed! Unlucky!");
	if (errcode == ERR_MUTEX)
		printf("Error! A pthread_mutex_*() failed!");
}

static void	free_t_sim(t_sim *sim)
{
	free(sim->input);
	free(sim);
}

static int	parse_input(t_sim *sim, int argc, char ** argv)
{
	t_input	*input;

	if (argc != 5 && argc != 6)
		return (ERR_ARG);
	input = malloc(sizeof(*input) * 1);
	if (input == NULL)
		return (ERR_MALLOC);
	input->nb_philo = atoi(argv[1]);
	input->time2die = atoi(argv[2]);
	input->time2eat = atoi(argv[3]);
	input->time2sleep = atoi(argv[4]);
	if (argv[5] != NULL)
		input->nb_meal_max = atoi(argv[5]);
	else
		input->nb_meal_max = -1;
	sim->input = input;
	return (ERR_OK);
}

static int	check_input(t_sim *sim)
{
	if (sim->input->nb_philo < 2)
		return (ERR_ARG);
	if (sim->input->time2die < 0)
		return (ERR_ARG);
	if (sim->input->time2eat < 0)
		return (ERR_ARG);
	if (sim->input->time2sleep < 0)
		return (ERR_ARG);
	if (sim->input->nb_meal_max < -1)
		return (ERR_ARG);
	return (ERR_OK);
}

static int	init_forks(t_sim *sim)
{
	t_fork	*forks;
	int		i;

	forks = calloc(sizeof(*forks), sim->input->nb_philo);
	if (forks == NULL)
		return (ERR_MALLOC);
	i = 0;
	while (i < sim->input->nb_philo)
	{
		forks[i].state = AVAIL;
		if (pthread_mutex_init(&forks[i].mutex, NULL) != 0)
			return (ERR_MUTEX);
		i++;
	}
	sim->forks = forks;
	return (ERR_OK);
}

// static int	init_philo(t_sim *sim)
// {
//
// }

static int	init_sim(t_sim *sim, int argc, char **argv)
{
	int	errcode;

	errcode = parse_input(sim, argc, argv);
	// if (errcode != ERR_OK)
	// 	return (errcode);
	errcode = check_input(sim);
	// if (errcode != ERR_OK)
	// 	return (errcode);
	errcode = init_forks(sim);
	// if (errcode != ERR_OK)
	// 	return (errcode);
	// errcode = init_philo(sim)
	// if (errcode != ERR_OK)
	// 	return (errcode);
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
}
