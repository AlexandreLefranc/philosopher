/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:17:33 by alefranc          #+#    #+#             */
/*   Updated: 2022/06/22 12:24:16 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo2.h"

// static long int	get_time_since(struct timeval t0)
// {
// 	long int		diff;
// 	struct timeval	t1;
//
// 	if (gettimeofday(&t1, NULL) != 0)
// 		return (-1);
// 	diff = 0;
// 	diff += (t1.tv_sec - t0.tv_sec) * 1000;
// 	diff += (t1.tv_usec - t0.tv_usec) / 1000;
// 	return (diff);
// }

static void	free_t_sim(t_sim *sim)
{
	free(sim->input);
	free(sim->forks);
	free(sim->philos);
	free(sim);
}

// static void	*routine(void *arg)
// {
// 	t_philo	*philo;
//
// 	philo = (t_philo *)arg;
// 	philo->last_meal
// 	while (1);
// 	return (NULL);
// }

static int	start_sim(t_sim *sim)
{
	(void)sim;
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
	start_sim(sim);
	monitor_sim(sim);
	free_t_sim(sim);
	return (0);
}
