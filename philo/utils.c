/*HEADER*/

#include "philo.h"

void	clean_up(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->msg_lock);
	pthread_mutex_lock(&data->meals_lock);
	pthread_mutex_unlock(&data->meals_lock);
	pthread_mutex_destroy(&data->meals_lock);
	pthread_mutex_destroy(&data->dead_lock);
	if (data->forks)
	{
		while (i < data->n_philo)
		{
			pthread_mutex_destroy(&data->philo[i].eat_lock);
			pthread_mutex_lock(&data->philo[i].dead_lock);
			pthread_mutex_unlock(&data->philo[i].dead_lock);
			pthread_mutex_destroy(&data->philo[i].dead_lock);
			pthread_mutex_destroy(&data->forks[i++]);
		}
	}
	free_data(data);
}

size_t	get_time(void)
{
	struct timeval	time_struct;
	size_t	time;

	gettimeofday(&time_struct, NULL);
	time = time_struct.tv_sec * 1000 + time_struct.tv_usec / 1000;
	return (time);
}

void	print_msg(t_data *data, int id, char *msg)
{
	size_t	time;

	pthread_mutex_lock(&data->msg_lock);
	time = get_time() - data->t_start;
	if (!check_death(data, 0, -1))
		printf("%lu %d %s\n", time, id, msg);
	else if (!ft_strncmp(msg, "died", 5))
		printf("%lu %d %s\n", time, id, msg);
	pthread_mutex_unlock(&data->msg_lock);
}

size_t	ft_strlen(const char *s)
{
	size_t	n;

	n = 0;
	while (s[n])
		n++;
	return (n);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	n2;

	n2 = 0;
	while ((s1[n2] || s2[n2]) && n2 < n)
	{
		if ((s1[n2] < s2[n2]))
			return (((unsigned char *)s1)[n2] -
			((unsigned char *)s2)[n2]);
		if (s1[n2] > s2[n2])
			return (((unsigned char *)s1)[n2] -
			((unsigned char *)s2)[n2]);
		n2++;
	}
	return (0);
}
