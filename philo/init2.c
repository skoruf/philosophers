/*HEADER*/

#include "philo.h"

void	init_philo(t_data *data)
{
	int	i;
	int	last;

	i = 0;
	last = data->n_philo - 1;
	while (i < data->n_philo)
	{
		pthread_mutex_init(&data->philo[i].eat_lock, NULL);
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		data->philo[i].times_eaten = 0;
		data->philo[i].t_last_meal = get_time();
		data->philo[i].l_fork = &data->forks[last];
		data->philo[i].r_fork = &data->forks[i];
		last = i;
		i++;
	}
}

int	init_args(t_data *data, char **argv, int argc)
{
	size_t	*args;

	args = malloc(sizeof(int *) * 5);
	if (!args)
		return (1);
	if (check_overflow(args, argv, argc))
		return (free(args), 1);
	if (args[0] > INT_MAX)
		return (free(args), printf("Nr of philos too high\n"), 1);
	data->n_philo = args[0];
	data->t_die = args[1];
	data->t_eat = args[2];
	data->t_sleep = args[3];
	data->meals = args[4];
	return (free(args), 0);
}

int	init_data(t_data *data, char **argv, int argc)
{
	int	i;

	i = 0;
	if (init_args(data, argv, argc))
		return (1);
	data->t_start = get_time();
	data->forks = NULL;
	data->philo = NULL;
	data->dead = 0;
	data->done_eating = 0;

	pthread_mutex_init(&data->msg_lock, NULL);
	pthread_mutex_init(&data->eat_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->forks || !data->philo)
		return (free_data(data), 1);
	while (i < data->n_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	init_philo(data);
	
	return (0);
}
