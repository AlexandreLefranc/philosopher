#include "philo2.h"

static int	is_in_advance(t_sim *sim, int i)
{
	int	nb_philo;

	nb_philo = sim->input->nb_philo;

	if (sim->philos[i].nb_meals > sim->philos[(i + 1) % nb_philo].nb_meals)
		return (1);
	if (sim->philos[i].nb_meals > sim->philos[(i - 1) % nb_philo].nb_meals)
		return (1);
	return (0);
}

static void	give_orders(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->input->nb_philo)
	{
		if (is_in_advance(sim, i) == 1)
			sim->philos[i].allowed = 0;
		else
			sim->philos[i].allowed = 1;
		i++;
	}
}

int	monitor_sim(t_sim *sim)
{
	int	i;

	while (sim->any_death == 0)
	{
		give_orders(sim);
		usleep(sim->input->time2sleep / 2);
		// printf("Hi\n");
	}
	i = 0;
	while (i < sim->input->nb_philo)
	{
		pthread_join(sim->philos[i].thread, NULL);
		i++;
	}
	return (ERR_OK);
}
