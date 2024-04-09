/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:10:34 by cthaler           #+#    #+#             */
/*   Updated: 2023/11/30 12:10:36 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
size_t	get_t_ms()
{
}
*/

int	eat(t_philo *ph, int flag)
{
	if (flag == 1)
	{
		pthread_mutex_lock(ph->r_fork);
		print_msg(ph->data, ph->id, "has taken a fork");
		pthread_mutex_lock(ph->l_fork);
		print_msg(ph->data, ph->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(ph->l_fork);
		print_msg(ph->data, ph->id, "has taken a fork");
		pthread_mutex_lock(ph->r_fork);
		print_msg(ph->data, ph->id, "has taken a fork");
	}
	print_msg(ph->data, ph->id, "is eating");
	ph->times_eaten++;
	if (ph->data->meals && ph->times_eaten == ph->data->meals)
	{
		pthread_mutex_lock(&ph->data->eat_lock);
		ph->data->done_eating++;
		pthread_mutex_unlock(&ph->data->eat_lock);
	}
	//TESTING
	size_t test = get_time() - ph->t_last_meal;
	if (test + ph->data->t_eat >= ph->data->t_die)
	{
		if (ph->data->t_die < ph->data->t_eat)
		{
			pthread_mutex_lock(&ph->data->dead_lock);
			usleep((ph->data->t_die - test) * 1000);
			ph->data->dead = 1;
			pthread_mutex_unlock(&ph->data->dead_lock);
		}
		pthread_mutex_unlock(ph->r_fork);
		pthread_mutex_unlock(ph->l_fork);
		return (1);
	}
	usleep(ph->data->t_eat * 1000);
	pthread_mutex_lock(&ph->eat_lock);
	ph->t_last_meal = get_time();
	pthread_mutex_unlock(&ph->eat_lock);
	pthread_mutex_unlock(ph->r_fork);
	pthread_mutex_unlock(ph->l_fork);
	return (0);
}

int	check_death(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	if (data->dead)
	{
		pthread_mutex_unlock(&data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->dead_lock);
	return (0);
}

void	*routine(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *) philo;

	int test = 0;
	//TESTING
	while (!check_death(ph->data))
	{
		if( ph->data->meals &&
			ph->data->done_eating == ph->data->n_philo)
			break ;
		if (ph->id % 2)
		{
			if (eat(ph, 1))
				break ;
		}
		else
		{
			if (eat(ph, 2))
				break ;
		}
		print_msg(ph->data, ph->id, "is sleeping");
		usleep(ph->data->t_sleep * 1000);
		print_msg(ph->data, ph->id, "is thinking");
		test++;
	}
	return (NULL);
}

int	check_mate(t_philo *ph, t_data *data)
{
	int	i;
	size_t	time;

	i = 0;
	time = get_time();
	while (i < data->n_philo)
	{
		pthread_mutex_lock(&ph->eat_lock);
		if (check_death(data) || time - ph[i].t_last_meal >= data->t_die)
		{
			data->dead = 1;
			pthread_mutex_unlock(&ph->eat_lock);
			print_msg(data, ph[i].id, "died");
			return (1);
		}
		pthread_mutex_unlock(&ph->eat_lock);
		i++;
	}
	return (0);
}

void	*lord_routine(void *data_p)
{
	t_data	*data;

	data = (t_data *)data_p;
	//TESTING
	//int test = 0;
	while (!check_mate(data->philo, data)
		&& (data->meals && data->n_philo > data->done_eating))
	{
		usleep(500);
		//TESTING
		//if (test > 5)
		//	break ;
		//test++;
		//if (data->meals && check_if_full(data->philo, data))
		//	break ;
	}
	return (NULL);
}

int	init_thread(t_data *data)
{
	int	i;
	pthread_t	overlord;

	i = 0;
	if (pthread_create(&overlord, NULL, &lord_routine, data))
			return (1);
	while (i < data->n_philo)
	{
		//on failure join those that were created
		//then clean up and return
		if (pthread_create(&data->philo[i].thr_p, NULL,
			&routine, &data->philo[i]))
			return (1);
		i++;
	}
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_join(data->philo[i].thr_p, NULL))
			return (1);
		i++;
	}
	return (0);
}
