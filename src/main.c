/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 13:18:35 by alefranc          #+#    #+#             */
/*   Updated: 2022/04/20 12:53:39 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_input			input;
	pthread_mutex_t	*forks;
	pthread_t		*philos;

	if (parse_input(&input, argc, argv) == -1)
		return (1);
	printf("nb_philo=%d, die=%d, eat=%d, sleep=%d\n", input.nb_philo, input.time2die, input.time2eat, input.time2sleep);
	forks = init_forks(input.nb_philo);
	philos = init_philos(&input);
	destroy_forks(&forks, input.nb_philo);
	return (0);
}
