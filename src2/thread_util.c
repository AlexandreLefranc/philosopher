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

int	is_dead(t_philo *self)
{
	if (get_time_since(self->t_lastmeal) > self->sim->input->time2die)
	{
		printf("%ld %d died\n", get_time_since(self->sim->t0), self->id);
		self->sim->any_death = 1;
		return (1);
	}
	return (0);
}
