/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 03:35:50 by alefranc          #+#    #+#             */
/*   Updated: 2022/06/28 03:48:20 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_t_sim(t_sim *sim)
{
	free(sim->forks);
	free(sim->input);
	free(sim->philos);
	free(sim);
}

long int	time_since(struct timeval t0)
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

void	print_usage(void)
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

void	print_err(int errcode)
{
	if (errcode == ERR_ARG)
	{
		printf("Error! Invalid arguments!\n");
		print_usage();
	}
	if (errcode == ERR_MALLOC)
		printf("Error! A malloc() failed! Unlucky!\n");
	if (errcode == ERR_MUTEX)
		printf("Error! A pthread_mutex_*() failed!\n");
	if (errcode == ERR_TIME)
		printf("Error! A gettimeofday() failed!\n");
}
