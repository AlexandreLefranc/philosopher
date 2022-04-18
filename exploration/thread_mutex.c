/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 18:11:25 by alefranc          #+#    #+#             */
/*   Updated: 2022/04/18 18:14:14 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# include <stdio.h>

int i = 0;

void	*routine(void *arg)
{
	(void)arg;
	for (int j = 0; j < 1000000; j++)
		i++;
	return (NULL);
}

int main(void)
{
	pthread_t	t;
	pthread_create(&t, NULL, &routine, NULL);

	pthread_t	t2;
	pthread_create(&t2, NULL, &routine, NULL);

	pthread_join(t, NULL);
	pthread_join(t2, NULL);

	printf("%d\n", i);
	return (0);
}
