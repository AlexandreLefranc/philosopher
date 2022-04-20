/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:19:35 by alefranc          #+#    #+#             */
/*   Updated: 2022/04/20 12:47:33 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*init_forks(int nb_philo)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(*forks) * nb_philo);
	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

int	destroy_forks(pthread_mutex_t **forks, int nb_philo)
{
	pthread_mutex_t	*forks_tmp;
	int				i;

	forks_tmp = *forks;
	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_destroy(&forks_tmp[i]);
		i++;
	}
	free(*forks);
	return (0);
}
