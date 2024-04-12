/*INCLUDE HEADER*/
//Args: 
	//number_of_philosophers
	//time_to_die
	//time_to_eat
	//time_to_sleep
	//number_of_times_each_philo_must_eat

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (printf("Error: number of args invalid\n"), 1);
	if (argv[5] && !ft_strncmp(argv[5], "0", 2))
		return (0);
	if (init_data(&data, argv, argc))
		return (printf("Error: init_data\n"), 1);
	if (init_thread(&data))
		return (printf("Error: init_thread\n"), clean_up(&data), 1);
	return (clean_up(&data), 0);
}
