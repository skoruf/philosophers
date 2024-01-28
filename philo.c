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
	pthread_mutex_t	*forks;
	t_philo		*philo;
}				t_data;

//	pthread_mutex_t	mutex;
//	int	count = 0;



void	*routine(void *philo)
{
	t_philo	*phi;

	phi = (t_philo *) philo;
	int test = 0;
	//TESTING
	/*
	while (test < 10)
	{
		if (phi->id % 2)
		{
			pthread_mutex_lock(phi->r_fork);
			pthread_mutex_lock(phi->l_fork);
		}
		else
		{
			pthread_mutex_lock(phi->l_fork);
			pthread_mutex_lock(phi->r_fork);
		}
		printf("Philo %d is eating\n", phi->id);
		test++;
		sleep(1);
		pthread_mutex_unlock(phi->r_fork);
		pthread_mutex_unlock(phi->l_fork);
		pthread_join(phi->thr_p, NULL);
	}*/
	/*
	int i = 0;
	while (i < 1000)
	{
		pthread_mutex_lock(&mutex);
		i++;
		count++;
		pthread_mutex_unlock(&mutex);
	}
	*/
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
		data->philo->id = i + 1;
		data->philo->l_fork = &data->forks[last];
		data->philo->r_fork = &data->forks[i];
		last = i;
		i++;
	}
}

void	init_data(t_data *data)
{
	int	i;

	i = 0;
	//TESTING
	data->n_philo = 5;
	while (i < 5)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	init_philo(data);
}

int	init_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (!pthread_create(&data->philo->thr_p, NULL,
			&routine, &data->philo[i]))
			return (0);
		i++;
	}
	return (1);
}

int	main(void)
{
	t_data	data;

	init_data(&data);
	//init_thread(&data);
	
	
/*
	pthread_t p1, p2;

	pthread_mutex_init(&mutex, NULL);
	pthread_create(&p1, NULL, &routine, NULL);
	pthread_create(&p2, NULL, &routine, NULL);
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	
	pthread_mutex_destroy(&mutex);
	printf("Count: %d\n", count);

	struct timeval tv;
	struct timeval tv2;
	//struct timezone tz;

	gettimeofday(&tv, NULL);
	usleep(10000);
	gettimeofday(&tv2, NULL);
	printf("Microseconds: %ld\n",tv2.tv_usec - tv.tv_usec);
*/
	return (0);
}
