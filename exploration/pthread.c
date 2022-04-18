/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 18:05:21 by alefranc          #+#    #+#             */
/*   Updated: 2022/04/18 18:09:23 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# include <stdio.h>

void	*routine(void *arg)
{
	(void)arg;
	printf("Start of thread\n");
	sleep(2);
	printf("End of thread\n");
	return (NULL);
}

int	main(void)
{
	pthread_t	t;
	pthread_create(&t, NULL, &routine, NULL);

	pthread_t	t2;
	pthread_create(&t2, NULL, &routine, NULL);

	pthread_join(t, NULL);
	pthread_join(t2, NULL);
}
