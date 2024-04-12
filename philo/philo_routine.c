/*HEADER*/

#include "philo.h"

void	eat_option(t_philo *ph, int flag)
{
	if (flag)
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
}

int	eat(t_philo *ph)
{
	eat_option(ph, ph->id % 2);
	if (ph->data->meals && ph->times_eaten == ph->data->meals)
	{
		pthread_mutex_lock(&ph->data->meals_lock);
		ph->data->done_eating++;
		pthread_mutex_unlock(&ph->data->meals_lock);
	}
	if (get_time() > ph->data->t_die + ph->t_last_meal)
	{
		pthread_mutex_unlock(ph->r_fork);
		pthread_mutex_unlock(ph->l_fork);
		return (0);
	}
	pthread_mutex_lock(&ph->eat_lock);
	ph->t_last_meal = get_time();
	pthread_mutex_unlock(&ph->eat_lock);
	ft_usleep(ph->data->t_eat);
	pthread_mutex_unlock(ph->r_fork);
	pthread_mutex_unlock(ph->l_fork);
	return (0);
}

int	philo_sleep(t_philo *ph)
{
	size_t	time_since;
	
	time_since = get_time() - ph->t_last_meal;
	print_msg(ph->data, ph->id, "is sleeping");
	if (time_since + ph->data->t_sleep > ph->data->t_die)
	{
		ft_usleep(ph->data->t_die - time_since);
		return (0);
	}
	ft_usleep(ph->data->t_sleep);
	return (0);
}

int	check_meals(t_data *data)
{
	if (data->meals)
	{
		pthread_mutex_lock(&data->meals_lock);
		if (data->done_eating == data->n_philo)
		{
			pthread_mutex_unlock(&data->meals_lock);
			return (1);
		}
		pthread_mutex_unlock(&data->meals_lock);
	}
	return (0);
}

void	*routine(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *) philo;

	if (ph->data->n_philo == 1)
	{
		print_msg(ph->data, ph->id, "has taken a fork");
		ft_usleep(ph->data->t_die);
		print_msg(ph->data, ph->id, "died");
		return (NULL);
	}
	while (!check_death(ph->data, 1, ph->id - 1) && !check_meals(ph->data))
	{
		eat(ph);
		philo_sleep(ph);
		print_msg(ph->data, ph->id, "is thinking");
		if (ph->data->t_sleep <= ph->data->t_eat)
			ft_usleep(ph->data->t_eat - ph->data->t_sleep + 2);
	}
	return (NULL);
}
