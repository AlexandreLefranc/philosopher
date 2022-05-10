/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:47:51 by alefranc          #+#    #+#             */
/*   Updated: 2022/05/10 17:09:35 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_t	*init_philos(t_input	*input)
{
	pthread_t	*philos;

	philos = malloc(sizeof(*philos) * input->nb_philo);
	return (philos);
}

int		destroy_philos(pthread_t	**philos)
{
	free(*philos);
	return (0);
}
