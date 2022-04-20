/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 18:11:25 by alefranc          #+#    #+#             */
/*   Updated: 2022/04/20 16:22:34 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# include <stdio.h>

int i = 0;
pthread_mutex_t	mutex;

void	*routine(void *arg)
{
	// printf("%lu\n %ld\n", sizeof(mutex), mutex.__align);
	pthread_mutex_lock(&mutex);
	printf("%lu\n %ld\n", sizeof(mutex), mutex.__align);
	(void)arg;
	for (int j = 0; j < 1000000; j++)
		i++;
	pthread_mutex_unlock(&mutex);
	return (NULL);
}

int main(void)
{

	pthread_mutex_init(&mutex, NULL);

	pthread_t	t;
	pthread_create(&t, NULL, &routine, NULL);

	pthread_t	t2;
	pthread_create(&t2, NULL, &routine, NULL);

	pthread_join(t, NULL);
	pthread_join(t2, NULL);

	printf("%lu\n %ld\n", sizeof(mutex), mutex.__align);
	pthread_mutex_destroy(&mutex);

	printf("%d\n", i);
	return (0);
}
