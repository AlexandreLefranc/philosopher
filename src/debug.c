#include "philo.h"

void	print_input(t_input *input)
{
	printf("nb_philo = %d\n", input->nb_philo);
	printf("time2die = %d\n", input->time2die);
	printf("time2eat = %d\n", input->time2eat);
	printf("time2sleep = %d\n", input->time2sleep);
	printf("nb_meal_max = %d\n", input->nb_meal_max);
	printf("\n");
}

void	print_philo(t_philo_id_card *philo)
{
	int	i;
	int	max;

	max = philo[0].input->nb_philo;
	i = 0;
	while (i < max)
	{
		printf("philo[%d].id = %d\n", i, philo[i].id);
		printf("philo[%d].start_existance = %ld %ld\n", i, philo[i].start_existance.tv_sec, philo[i].start_existance.tv_usec);
		printf("philo[%d].last_meal =       %ld %ld\n", i, philo[i].last_meal.tv_sec, philo[i].last_meal.tv_usec);
		printf("philo[%d].nb_meals = %zu\n", i, philo[i].nb_meals);
		printf("philo[%d].forks = ", i);
		for (int j = 0; j < max; j++)
			printf("%d ", philo[i].forks[j]);
		printf("\n");
		printf("\n");
		i++;
	}
}
