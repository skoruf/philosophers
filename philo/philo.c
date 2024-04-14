/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <cthaler@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:10:34 by cthaler           #+#    #+#             */
/*   Updated: 2023/11/30 12:10:36 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_data *data, int flag, int i)
{
	if (!flag)
	{
		pthread_mutex_lock(&data->dead_lock);
		if (data->dead)
			return (pthread_mutex_unlock(&data->dead_lock), 1);
		pthread_mutex_unlock(&data->dead_lock);
	}
	else
	{
		pthread_mutex_lock(&data->philo[i].dead_lock);
		if (data->philo[i].dead)
		{
			pthread_mutex_unlock(&data->philo[i].dead_lock);
			return (1);
		}
		pthread_mutex_unlock(&data->philo[i].dead_lock);
	}
	return (0);
}

static void	set_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_lock(&data->philo[i].dead_lock);
		data->philo[i].dead = 1;
		pthread_mutex_unlock(&data->philo[i].dead_lock);
		i++;
	}
}

static void	check_mate(t_data *data, int i)
{
	pthread_mutex_lock(&data->dead_lock);
	data->dead = 1;
	pthread_mutex_unlock(&data->dead_lock);
	print_msg(data, data->philo[i].id, "died");
	set_dead(data);
}

void	*lord_routine(void *data_p)
{
	int		i;
	t_philo	*ph;
	t_data	*data;

	data = (t_data *)data_p;
	ph = data->philo;
	while (!check_meals(data))
	{
		i = 0;
		while (i < data->n_philo)
		{
			pthread_mutex_lock(&ph[i].eat_lock);
			if (get_time() - ph[i].t_last_meal > data->t_die)
			{
				pthread_mutex_unlock(&ph[i].eat_lock);
				return (check_mate(data, i), NULL);
			}
			pthread_mutex_unlock(&ph[i].eat_lock);
			i++;
		}
		usleep(42);
	}
	return (NULL);
}
