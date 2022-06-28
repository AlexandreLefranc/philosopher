/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 03:35:33 by alefranc          #+#    #+#             */
/*   Updated: 2022/06/28 03:52:22 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_sim	*sim;
	int		errcode;
	int		i;

	sim = ft_calloc(sizeof(*sim), 1);
	if (sim == NULL)
		return (ERR_MALLOC);
	errcode = init_sim(sim, argc, argv);
	if (errcode != ERR_OK)
		return (free_t_sim(sim), print_err(errcode), errcode);
	start_sim(sim);
	monitor_sim(sim);
	i = 0;
	while (i < sim->input->nb_philo)
	{
		pthread_join(sim->philos[i].thread, NULL);
		i++;
	}
	free_t_sim(sim);
}
