/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 13:18:35 by alefranc          #+#    #+#             */
/*   Updated: 2022/05/31 17:51:53 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_t_table(t_table *table)
{
	free(table->forks);
	free(table->philos);
}

static int	init_t_table(t_table *table, t_input input)
{
	table->forks = calloc(sizeof(*table->forks), input.nb_philo);
	if (table->forks == NULL)
		return (1);
	table->philos = calloc(sizeof(*table->philos), input.nb_philo);
	if (table->philos == NULL)
		return (free(table->forks), 1);
	return (0);
}

static t_thread_arg	*start_sim(t_input input, t_table table)
{

}

int	main(int argc, char **argv)
{
	t_input	input;
	t_table	table;

	if (parse_input(&input, argc, argv) != 0)
		return (1);
	printf("nb_philo=%d, die=%d, eat=%d, sleep=%d, nb_meals=%d\n", input.nb_philo, input.time2die, input.time2eat, input.time2sleep, input.nb_meal_max);
	if (init_t_table(&table, input) != 0)
		return (1);

	run_sim(input, table);

	return (0);
}
