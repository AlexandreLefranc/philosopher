#include "philo.h"

void	*routine(void *arg)
{
	t_philo_id_card *id_card;

	id_card = (t_philo_id_card *)arg;
	while (*(id_card->running) == 1 && (id_card->input->nb_meals_max == -1
			|| id_card->nb_meals < id_card->input->nb_meal_max))
	{
		if (id_card->left_fork == FREE && id_card->right_fork == FREE)
		{
			pthread_mutex_lock(id_card->handle_fork);
			if (id_card->left_fork == FREE && id_card->right_fork == FREE)
			{
				id_card->left_fork == USED;
				print_taking_fork(id_card);
				id_card->right_fork == USED;
				print_taking_fork(id_card);
				pthread_mutex_unlock(id_card->handle_fork);
			}
			else
			{
				pthread_mutex_unlock(id_card->handle_fork);
				continue ;
			}
			id_card->last_meal = gettimeofday(id_card->last_meal, NULL);
			id_card->nb_meals++;
			print_eating(id_card);
			usleep(id_card->input->time2eat * 1000);
			id_card->left_fork == FREE;
			id_card->right_fork == FREE;
			print_sleeping(id_card);
			usleep(id_card->input->time2sleep * 1000);
		}
	}
}
