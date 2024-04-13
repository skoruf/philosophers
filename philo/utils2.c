/*HEADER*/

#include "philo.h"

void	ft_usleep(size_t time)
{
	size_t	cur_time;

	cur_time = get_time();
	while (get_time() < (cur_time + time))
		usleep(500);
}

void	free_data(t_data *data)
{
	if (data->forks)
		free(data->forks);
	if (data->philo)
		free(data->philo);
}

void	nap(t_data *data)
{
	if (data->n_philo > 20 && data->t_sleep <= data->t_eat)
			ft_usleep(data->t_eat - data->t_sleep
				+ data->t_eat / 10);
		else
			ft_usleep(2);
}

void	destroy_forks(t_data *data, int i)
{
	while (i >= 0)
		pthread_mutex_destroy(&data->forks[i--]);
}
