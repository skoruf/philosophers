/*HEADER*/

#include "philo.h"

void	join_threads(t_data *data, int j, pthread_t overlord, int flag)
{
	int	i;

	i = 0;
	while (i <= j)
	{
		if (pthread_join(data->philo[i].thr_p, NULL))
			printf("Error: join thread nr %d\n", i);
		i++;
	}
	if (flag)
		pthread_detach(overlord);
}

int	init_thread(t_data *data)
{
	int	i;
	pthread_t	overlord;

	i = 0;
	while (i < data->n_philo)
	{
		data->philo[i].t_last_meal = get_time();
		if (pthread_create(&data->philo[i].thr_p, NULL,
			&routine, &data->philo[i]))
			return (join_threads(data, i, overlord, 0), 1);
		i++;
	}
	data->t_start = get_time();
	if (pthread_create(&overlord, NULL, &lord_routine, data))
			return (join_threads(data, i, overlord, 0), 1);
	join_threads(data, i - 1, overlord, 1);
	return (0);
}
