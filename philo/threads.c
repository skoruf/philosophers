/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <cthaler@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 12:05:15 by cthaler           #+#    #+#             */
/*   Updated: 2024/04/13 12:05:19 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_threads(t_data *data, int j, pthread_t overlord, int flag)
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
	int			i;
	pthread_t	overlord;

	overlord = 0;
	i = 0;
	data->t_start = get_time();
	while (i < data->n_philo)
	{
		data->philo[i].t_last_meal = get_time();
		if (pthread_create(&data->philo[i].thr_p, NULL,
				&routine, &data->philo[i]))
			return (join_threads(data, i - 1, overlord, 0), 1);
		i++;
	}
	if (data->n_philo == 1)
		return (join_threads(data, i - 1, overlord, 0), 0);
	if (pthread_create(&overlord, NULL, &lord_routine, data))
		return (join_threads(data, i, overlord, 0), 1);
	join_threads(data, i - 1, overlord, 1);
	return (0);
}
