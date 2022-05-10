/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 13:18:35 by alefranc          #+#    #+#             */
/*   Updated: 2022/05/10 18:09:33 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	start_simu()

int	main(int argc, char **argv)
{
	t_input			input;
	pthread_mutex_t	*forks;
	pthread_t		*philos;

	if (parse_input(&input, argc, argv) == -1)
		return (1);
	printf("nb_philo=%d, die=%d, eat=%d, sleep=%d, nb_meals=%d\n", input.nb_philo, input.time2die, input.time2eat, input.time2sleep, input.nb_meals);
	forks = init_forks(input.nb_philo);
	philos = init_philos(&input);

	// start_simu();

	destroy_forks(&forks, input.nb_philo);
	destroy_philos(&philos);


	return (0);
}
