#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <limits.h>

typedef struct	s_philo
{
	int		id;
	size_t	times_eaten;
	size_t	t_last_meal;
	pthread_t	thr_p;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	eat_lock;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	int		n_philo;
	int		dead;
	int		done_eating;
	size_t		t_start;
	size_t		t_die;
	size_t		t_eat;
	size_t		t_sleep;
	size_t		meals;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	msg_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	*forks;
	t_philo		*philo;
}				t_data;

int	init_thread(t_data *data);
int	init_data(t_data *data, char **argv, int argc);
void	free_data(t_data *data);
size_t	ft_strlen(const char *s);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	check_overflow(size_t *args, char **argv, int argc);
void	print_msg(t_data *data, int id, char *msg);
size_t	get_time(void);
void	clean_up(t_data *data);
void	free_data(t_data *data);
int	check_death(t_data *data);
