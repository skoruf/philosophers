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

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct	s_philo
{
	int		id;
	pthread_t	thr_p;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	int		n_philo;
	size_t		t_start;
	size_t		t_die;
	size_t		t_eat;
	size_t		t_sleep;
	pthread_mutex_t	*forks;
	t_philo		*philo;
}				t_data;

size_t	get_t_ms()
{
}

void	sleeping(t_philo *ph)
{
	printf("Philo %d is sleeping\n", ph->id);
	//TESTING
	usleep(200 * 1000);
}

void	eat(t_philo *ph, int flag)
{
	if (flag == 1)
	{
		pthread_mutex_lock(ph->r_fork);
		printf("Philo %d has taken a fork\n", ph->id);
		pthread_mutex_lock(ph->l_fork);
		printf("Philo %d has taken a fork\n", ph->id);
	}
	else
	{
		pthread_mutex_lock(ph->l_fork);
		printf("Philo %d has taken a fork\n", ph->id);
		pthread_mutex_lock(ph->r_fork);
		printf("Philo %d has taken a fork\n", ph->id);
	}
	printf("Philo %d is eating\n", ph->id);
	//TESTING
	usleep(ph->data->t_eat);
	pthread_mutex_unlock(ph->r_fork);
	pthread_mutex_unlock(ph->l_fork);
}

void	*routine(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *) philo;

	int test = 0;
	//TESTING
	while (test < 10)
	{
		if (ph->id % 2)
			eat(ph, 1);
		else
			eat(ph, 2);
		sleeping(ph);
		printf("Philo %d is thinking\n", ph->id);
		test++;
	}
	return (NULL);
}

void	init_philo(t_data *data)
{
	int	i;
	int	last;

	i = 0;
	last = data->n_philo - 1;
	while (i < data->n_philo)
	{
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		data->philo[i].l_fork = &data->forks[last];
		data->philo[i].r_fork = &data->forks[i];
		last = i;
		i++;
	}
}

void	free_data(t_data *data)
{
	if (data->forks)
		free(data->forks);
	if (data->philo)
		free(data->philo);
}

int	init_data(t_data *data)
{
	int	i;

	i = 0;
	//TESTING
	data->n_philo = 5;
	data->t_die = 500000;
	data->t_eat = 100000;
	data->t_sleep = 100000;
	//********
	data->t_start = 
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->forks || !data->philo)
		return (free_data(data), 0);
	while (i < 5)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	init_philo(data);
	return (1);
}

int	init_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_create(&data->philo[i].thr_p, NULL,
			&routine, &data->philo[i]))
			return (0);
		i++;
	}
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_join(data->philo[i].thr_p, NULL))
			return (0);
		i++;
	}
	return (1);
}

int	main(void)
{
	t_data	data;

	if (!init_data(&data))
		return (1);
	if (!init_thread(&data))
		return (free_data(&data), 1);
	return (0);
}
