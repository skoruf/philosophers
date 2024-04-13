/*HEADER*/

#include "philo.h"

void	destroy_failed(t_data *data, int i, int flag)
{
	if (flag)
		pthread_mutex_destroy(&data->philo[i + 1].eat_lock);
	while (i >= 0)
	{
		pthread_mutex_destroy(&data->philo[i].eat_lock);
		pthread_mutex_destroy(&data->philo[i].dead_lock);
		i--;
	}
}

int	init_philo(t_data *data)
{
	int	i;
	int	last;
	i = 0;
	last = data->n_philo - 1;
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(&data->philo[i].eat_lock, NULL))
			return (destroy_failed(data, i - 1, 0), 1);
		if (pthread_mutex_init(&data->philo[i].dead_lock, NULL))
			return (destroy_failed(data, i - 1, 1), 1);
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		data->philo[i].dead = 0;
		data->philo[i].times_eaten = 0;
		data->philo[i].l_fork = &data->forks[last];
		if (data->n_philo != 1)
			data->philo[i].r_fork = &data->forks[i];
		last = i;
		i++;
	}
	return (0);
}

int	init_args(t_data *data, char **argv, int argc)
{
	size_t	*args;

	args = malloc(sizeof(int *) * 5);
	if (!args)
		return (1);
	if (check_overflow(args, argv, argc, 1))
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

int	init_data_mutexes(t_data *data, int i)
{
	if (pthread_mutex_init(&data->dead_lock, NULL))
		return (1);
	if (pthread_mutex_init(&data->msg_lock, NULL))
		return (pthread_mutex_destroy(&data->dead_lock), 1);
	if (pthread_mutex_init(&data->meals_lock, NULL))
	{
		pthread_mutex_destroy(&data->dead_lock);
		pthread_mutex_destroy(&data->msg_lock);
		return (1);
	}
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(&data->forks[i++], NULL))
			return (destroy_forks(data, i - 1), 1);
	}
	return (0);
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
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->forks || !data->philo)
		return (free_data(data), 1);
	if (init_data_mutexes(data, i))
		return (1);
	if (init_philo(data))
		return (1);
	return (0);
}
