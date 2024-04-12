/*HEADER*/

#include "philo.h"

void	ft_usleep(size_t time)
{
	size_t	cur_time;

	cur_time = get_time();
	while (get_time() < (cur_time + time))
		usleep(1000);
}

void	free_data(t_data *data)
{
	if (data->forks)
		free(data->forks);
	if (data->philo)
		free(data->philo);
}
