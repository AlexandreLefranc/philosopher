#include "philo2.h"

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
	int		i;

	sim->forks = calloc(sizeof(*sim->forks), sim->input->nb_philo);
	if (sim->forks == NULL)
		return (ERR_MALLOC);
	i = 0;
	while (i < sim->input->nb_philo)
	{
		sim->forks[i].state = AVAIL;
		if (pthread_mutex_init(&sim->forks[i].mutex, NULL) != 0)
			return (ERR_MUTEX);
		i++;
	}
	return (ERR_OK);
}

static int	init_philo(t_sim *sim)
{
	int		i;

	sim->philos = calloc(sizeof(*sim->philos), sim->input->nb_philo);
	if (sim->philos == NULL)
		return (ERR_MALLOC);
	i = 0;
	while (i < sim->input->nb_philo)
	{
		sim->philos[i].id = i + 1;
		sim->philos[i].state = THINKING;
		sim->philos[i].nb_meals = 0;
		sim->philos[i].sim = sim;
		sim->philos[i].allowed = 1;
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
	return (ERR_OK);
}
