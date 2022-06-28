#include "philo3.h"

static void	free_t_sim(t_sim *sim)
{
	// int	i;
	//
	// i = 0;
	// while (i < sim->input->nb_philo)
	// {
	// 	pthread_mutex_destroy(&sim->forks[i]);
	// 	i++;
	// }
	free(sim->forks);
	free(sim->input);
	free(sim->philos);
	free(sim);
}

static long int	time_since(struct timeval t0)
{
	long int		diff;
	struct timeval	t1;

	if (gettimeofday(&t1, NULL) != 0)
	return (-1);
	diff = 0;
	diff += (t1.tv_sec - t0.tv_sec) * 1000;
	diff += (t1.tv_usec - t0.tv_usec) / 1000;
	return (diff);
}

static void	print_take_fork(t_philo *self)
{
	pthread_mutex_lock(&self->sim->gmutex);
	if (self->sim->any_death == 0)
		printf("\033[33m%ld %d has taken a fork\033[0m\n", time_since(self->sim->t0), self->id + 1);
	pthread_mutex_unlock(&self->sim->gmutex);
}

static void	print_eating(t_philo *self)
{
	pthread_mutex_lock(&self->sim->gmutex);
	if (self->sim->any_death == 0)
		printf("\033[32m%ld %d is eating\033[0m\n", time_since(self->sim->t0), self->id + 1);
		// printf("\033[32m%ld %d is eating (%d)\033[0m\n", time_since(self->sim->t0), self->id + 1, self->nb_meal);
	pthread_mutex_unlock(&self->sim->gmutex);
}

static void	print_sleeping(t_philo *self)
{
	pthread_mutex_lock(&self->sim->gmutex);
	if (self->sim->any_death == 0)
		printf("\033[35m%ld %d is sleeping\033[0m\n", time_since(self->sim->t0), self->id + 1);
	pthread_mutex_unlock(&self->sim->gmutex);
}

static void	print_thinking(t_philo *self)
{
	pthread_mutex_lock(&self->sim->gmutex);
	if (self->sim->any_death == 0)
		printf("\033[36m%ld %d is thinking\033[0m\n", time_since(self->sim->t0), self->id + 1);
	pthread_mutex_unlock(&self->sim->gmutex);
}

static void	print_usage()
{
	printf("Usage:\n");
	printf("  ./philo <nb_philo> <time2die> <time2eat> <time2sleep>\
	[<nb_meal>]\n");
	printf("nb_philo: Number of philosopher. Must be more than 1.\n");
	printf("time2die: Time before a philosopher dies from starvation (ms).\n");
	printf("time2eat: Time a philosopher takes to eat (ms).\n");
	printf("time2sleep: Time a philosopher takes to sleep (ms).\n");
	printf("nb_meal: Number of time each philosopher must eat.\n");
}

static void	print_err(int errcode)
{
	if (errcode == ERR_ARG)
	{
		printf("Error! Invalid arguments!\n");
		print_usage();
	}
	if (errcode == ERR_MALLOC)
		printf("Error! A malloc() failed! Unlucky!\n");
	if (errcode == ERR_MUTEX)
		printf("Error! A pthread_mutex_*() failed!\n");
	if (errcode == ERR_TIME)
		printf("Error! A gettimeofday() failed!\n");
}

static int	parse_input(t_sim *sim, int argc, char ** argv)
{
	t_input	*input;

	if (argc != 5 && argc != 6)
		return (ERR_ARG);
	input = malloc(sizeof(*input) * 1);
	if (input == NULL)
		return (ERR_MALLOC);
	input->nb_philo = atoi(argv[1]);
	input->time2die = atoi(argv[2]);
	input->time2eat = atoi(argv[3]);
	input->time2sleep = atoi(argv[4]);
	if (argv[5] != NULL)
		input->nb_meal_max = atoi(argv[5]);
	else
		input->nb_meal_max = -1;
	sim->input = input;
	return (ERR_OK);
}

static int	check_input(t_sim *sim)
{
	if (sim->input->nb_philo < 1)
		return (ERR_ARG);
	if (sim->input->time2die < 1)
		return (ERR_ARG);
	if (sim->input->time2eat < 1)
		return (ERR_ARG);
	if (sim->input->time2sleep < 1)
		return (ERR_ARG);
	if (sim->input->nb_meal_max < -1)
		return (ERR_ARG);
	return (ERR_OK);
}

static int	init_forks(t_sim *sim)
{
	int	i;

	sim->forks = malloc(sizeof(*sim->forks) * sim->input->nb_philo);
	if (sim->forks == NULL)
		return (ERR_MALLOC);
	i = 0;
	while (i < sim->input->nb_philo)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
			return (ERR_MUTEX);
		i++;
	}
	return (ERR_OK);
}

static int	init_philo(t_sim *sim)
{
	int	i;

	sim->philos = malloc(sizeof(*sim->philos) * sim->input->nb_philo);
	if (sim->philos == NULL)
		return (ERR_MALLOC);
	i = 0;
	while (i < sim->input->nb_philo)
	{
		sim->philos[i].id = i;
		sim->philos[i].lfork = sim->forks + ((i + 0) % sim->input->nb_philo);
		sim->philos[i].rfork = sim->forks + ((i + 1) % sim->input->nb_philo);
		sim->philos[i].nb_meal = 0;
		sim->philos[i].sim = sim;
		i++;
	}
	return (ERR_OK);
}

static int	init_sim(t_sim *sim, int argc, char **argv)
{
	int	errcode;

	errcode = parse_input(sim, argc, argv);
	if (errcode != ERR_OK)
		return (errcode);
	errcode = check_input(sim);
	if (errcode != ERR_OK)
		return (errcode);
	errcode = init_forks(sim);
	if (errcode != ERR_OK)
		return (errcode);
	errcode = init_philo(sim);
	if (errcode != ERR_OK)
		return (errcode);
	sim->any_death = 0;
	if (gettimeofday(&sim->t0, NULL) != 0)
		return (ERR_TIME);
	if (pthread_mutex_init(&sim->gmutex, NULL) != 0)
		return (ERR_MUTEX);
	return (ERR_OK);
}

static int	philo_forks_eat(t_philo *self)
{
	if (self->id % 2 == 0)
	{
		pthread_mutex_lock(self->lfork);
		print_take_fork(self);
		pthread_mutex_lock(self->rfork);
		print_take_fork(self);
	}
	else
	{
		pthread_mutex_lock(self->rfork);
		print_take_fork(self);
		pthread_mutex_lock(self->lfork);
		print_take_fork(self);
	}
	pthread_mutex_lock(&self->sim->gmutex);
	self->nb_meal++;
	gettimeofday(&self->t_lastmeal, NULL);
	pthread_mutex_unlock(&self->sim->gmutex);
	print_eating(self);
	usleep(self->sim->input->time2eat * 1000);

	pthread_mutex_unlock(self->rfork);
	pthread_mutex_unlock(self->lfork);
	return (ERR_OK);
}

static int	philo_sleep_think(t_philo *self)
{
	print_sleeping(self);
	usleep(self->sim->input->time2sleep * 1000);

	print_thinking(self);
	usleep(500);
	return (ERR_OK);
}

static int	life_keep_going(t_philo *self)
{
	int	ret;
	
	pthread_mutex_lock(&self->sim->gmutex);
	if (self->nb_meal != self->sim->input->nb_meal_max && self->sim->any_death == 0)
		ret = 1;
	else
		ret = 0;
	pthread_mutex_unlock(&self->sim->gmutex);
	return (ret);
}

static void	*life(void *arg)
{
	t_philo	*self;

	self = arg;
	if (self->id % 2 == 0)
		usleep(100);
	if (self->sim->input->nb_philo == 1)
	{
		print_take_fork(self);
		usleep((self->sim->input->time2die + 5) * 1000);
	}
	while (life_keep_going(self) == 1)
	{
		philo_forks_eat(self);
		philo_sleep_think(self);
	}
	return (NULL);
}

static int	start_sim(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->input->nb_philo)
	{
		sim->philos[i].t_lastmeal = sim->t0;
		pthread_create(&sim->philos[i].thread, NULL, life, sim->philos + i);
		i++;
	}
	return (ERR_OK);
}

static int	any_death(t_sim *sim)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&sim->gmutex);
	while (i < sim->input->nb_philo)
	{
		if (time_since(sim->philos[i].t_lastmeal) >= sim->input->time2die &&
			sim->philos[i].nb_meal != sim->input->nb_meal_max)
		{
			printf("\033[31m%ld %d died\033[0m\n", time_since(sim->t0), i + 1);
			pthread_mutex_unlock(&sim->gmutex);
			return (1);
		}
		i++;
	}
	pthread_mutex_unlock(&sim->gmutex);
	return (0);
}

static int	all_done(t_sim *sim)
{
	int	i;
	int	nb_done;
	int	all_done;

	nb_done = 0;
	i = 0;
	pthread_mutex_lock(&sim->gmutex);
	while (i < sim->input->nb_philo)
	{
		if (sim->philos[i].nb_meal == sim->input->nb_meal_max)
			nb_done++;
		i++;
	}
	if (nb_done == sim->input->nb_philo)
		all_done = 1;
	else
		all_done = 0;
	pthread_mutex_unlock(&sim->gmutex);
	return (all_done);
}

static int	monitor_sim(t_sim *sim)
{
	while (1)
	{
		if (any_death(sim) == 1)
		{
			pthread_mutex_lock(&sim->gmutex);
			sim->any_death = 1;
			pthread_mutex_unlock(&sim->gmutex);
			break;
		}
		if (all_done(sim) == 1)
			break;
		usleep(1000);
	}
	return (ERR_OK);
}

int	main(int argc, char **argv)
{
	t_sim	*sim;
	int		errcode;

	sim = calloc(sizeof(*sim), 1);
	if (sim == NULL)
		return (ERR_MALLOC);
	errcode = init_sim(sim, argc, argv);
	if (errcode != ERR_OK)
		return (free_t_sim(sim), print_err(errcode), errcode);
	start_sim(sim);
	monitor_sim(sim);
	for (int i = 0; i < sim->input->nb_philo; i++)
		pthread_join(sim->philos[i].thread, NULL);
	free_t_sim(sim);
}
