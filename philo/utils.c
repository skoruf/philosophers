/*HEADER*/

#include "philo.h"

void	free_data(t_data *data)
{
	if (data->forks)
		free(data->forks);
	if (data->philo)
		free(data->philo);
}

void	clean_up(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->msg_lock);
	pthread_mutex_destroy(&data->eat_lock);
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
	//get time missing
	time = get_time() - data->t_start;
	//if dead, print dead message, else
	if (!check_death(data))
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
