#include "philo2.h"

int	monitor_sim(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->input->nb_philo)
	{
		pthread_join(sim->philos[i].thread, NULL);
		i++;
	}
	return (ERR_OK);
}
