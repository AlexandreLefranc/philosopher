# philosopher

# Fonctions autorisées

General

- `void	*memset(void *s, int c, size_t n)`
- printf
- malloc
- free
- write

Time

- `int usleep(useconds_t usec)`: Sleep in micro seconds
- `int gettimeofday(struct timeval *tv, struct timezone *tz)`: Write timestamp in `tv`. `tz = NULL` is ok

Threads

- `int pthread_create(pthread_t *thread, NULL, void *(*routine)(void *), void *arg)`: Create a thread running the `routine(arg)` function
- `int pthread_detach(pthread_t thread)`
- `int pthread_join(pthread_t thread, void **retval)`: Wait for the thread to terminate and catch routine return into `retval`
- `int pthread_mutex_init(pthread_mutex_t *mutex,NULL)`: Initialize the mutex
- `int pthread_mutex_destroy(pthread_mutex_t *mutex)`: Destroy the mutex
- `int pthread_mutex_lock(pthread_mutex_t *mutex)`: Lock the mutex
- `int pthread_mutex_unlock(pthread_mutex_t *mutex)`: Unlock the mutex

# Consigne

Pas de libft. Pas de variable globale.

Le programme: `./philo <nb_philo> <time_to_die> <time_to_eat>
<time_to_sleep>`
- nb_philo: Nombre de philosophes, nombre de fourchettes
- time_to_die: Si un philo n'a pas commencé a manger xx millisecondes apres le DEBUT de son precedent repas, ou depuis le debut de la simu.
- time_to_eat: Temps pris pour manger. Le philo garde les fourchettes.
- time_to_sleep: Temps pris pour dormir

Les philos doivent: `manger -> dormir -> penser -> manger ...`

Une fourchette est entre chaque philosophe.
Chaque philo a besoins des 2 fourchettes pour manger

Chaque changement d'etat doit etre log:

- `TIME X has taken a fork`
- `TIME X is eating`
- `TIME X is sleeping`
- `TIME X is thinking`
- `TIME X died`

Check les morts toutes les 10ms.

# Pseudo Code

```
struct input
{
	int nb_philo;
	int time2die;
	int time2eat;
	int time2sleep;
}

struct philo
{
	int				id;
	input_t			*input;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	forks_t	*forks;
}

main:
	input_t			input;
	pthread_mutex_t	*forks;

	input = parse_input();

	forks = malloc(sizeof(*forks) * input->nb_philo)
	forks = init_forks();


```

```
routine(args):
	while (running):
		while (1):
			if (both forks available):
				lock handling_forks
				print(has taken fork)
				lock both forks
				unlock handling_forks
		last_meal = now
		print(eating)
		sleep(time2eat)
		unlock both forks
		print(sleeping)
		sleep(time2sleep)
		print(thinking)
```

```
Main:
	Recuperer les inputs_infos
	Creer les fouchettes mutex
	Lancer les philos
	Checker en boucle la vie des philos
	Join les philos

Routine: args = forks, philo_id, time_start, inputs_infos, keep_going_sim, nb_repas
	Tant que la simulation continue ET que le nb_repas n'est pas atteint :
		Attendre que les deux fourchettes soient dispo
		Si la simulation continue:
			Lock les fourchettes
			Manger
			Unlock les fourchettes
		Si la simulation continue:
			Dormir
		Si la simulation continue:
			Penser
```
