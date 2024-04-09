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
(void)argv;
(void)data;
//WARNING: WERROR FLAG NOT SET!!!
	if (argc != 5 && argc != 6)
		return (printf("Error: number of args invalid\n"), 1);	
	if (init_data(&data, argv, argc))
		return (1);
	if (init_thread(&data))
		return (free_data(&data), 1);
	return (0);
}
