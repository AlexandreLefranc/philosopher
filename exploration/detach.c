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

	sleep(1);

	pthread_detach(t);
	pthread_detach(t2);

	// pthread_join(t, NULL);
	// pthread_join(t2, NULL);
}
