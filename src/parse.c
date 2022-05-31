/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:02:25 by alefranc          #+#    #+#             */
/*   Updated: 2022/05/31 15:43:48 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_input(t_input *input, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (-1);
	input->nb_philo = atoi(argv[1]);
	input->time2die = atoi(argv[2]);
	input->time2eat = atoi(argv[3]);
	input->time2sleep = atoi(argv[4]);
	if (argv[5] != NULL)
		input->nb_meal_max = atoi(argv[5]);
	else
		input->nb_meal_max = -1;
	return (0);
}
