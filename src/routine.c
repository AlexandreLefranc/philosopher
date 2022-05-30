#include "philo.h"

struct s_arg
{
	int				*running;
	pthread_mutex_t	handle_fork;
	struct timeval	start_time;
	t_input			*input;

	size_t			id;
	int				*left_fork;
	int				*right_fork;
	size_t			nb_meals;
	struct timeval	last_meal;
};

void	*routine(void *arg)
{
	while (*(arg->running) == 1 && (arg->input->nb_meals_max == -1
			|| arg->nb_meals < arg->input->nb_meal_max))
	{
		if (arg->left_fork == FREE && arg->right_fork == FREE)
		{
			pthread_mutex_lock(arg->handle_fork);
			if (arg->left_fork == FREE && arg->right_fork == FREE)
			{
				arg->left_fork == USED;
				print_taking_fork(arg);
				arg->right_fork == USED;
				print_taking_fork(arg);
				pthread_mutex_unlock(arg->handle_fork);
			}
			else
			{
				pthread_mutex_unlock(arg->handle_fork);
				continue ;
			}
			arg->last_meal = gettimeofday(arg->last_meal, NULL);
			arg->nb_meals++;
			print_eating(arg);
			usleep(arg->input->time2eat * 1000);
			arg->left_fork == FREE;
			arg->right_fork == FREE;
			print_sleeping(arg);
			usleep(arg->input->time2sleep * 1000);
		}
	}
}
