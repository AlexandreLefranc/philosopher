#include "philo.h"

void	*routine(void *arg)
{
	while (running == 1 && (nb_meals_max == -1 || nb_meals < nb_meal_max))
	{
		if (/*both forks available*/)
		{
			// lock handle_forks
			// if (both forks still available)
				// take left_fork
				// take right_fork
				// unlock handle_forks
			// else
				// Unlock handle_forks
				// continue
			// set time last meal to now
			// increment nb_meals
			// print eating
			// sleep for time2eat
			// release left_fork
			// release right_fork

			// print sleeping
			// sleep for time2sleep
		}
	}
}
