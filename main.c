/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaid <mazaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 22:38:17 by mazaid            #+#    #+#             */
/*   Updated: 2025/06/12 15:23:31 by mazaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_data(t_data *data, int argc, char **argv)
{
	data->num_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->max_meals = ft_atoi(argv[5]);
	else
		data->max_meals = -1;
	data->dead = 0;
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->eat_mutex, NULL);
	data->start_time = get_time();
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philosopher	*philos;
	t_fork			*forks;
	pthread_t		monitor_thread;

	philos = NULL;
	forks = NULL;
	if (!validate_args(argc, argv))
		return (1);
	init_data(&data, argc, argv);
	philos = malloc(sizeof(t_philosopher) * data.num_philosophers);
	forks = malloc(sizeof(t_fork) * data.num_philosophers);
	if (!philos || !forks)
		return (free_and_cleanup(&data, forks, philos,
				"Error: Memory allocation failed."), 1);
	if (!init_forks_mutexes(&data, forks, philos))
		return (1);
	init_philosophers(&data, forks, philos);
	if (data.num_philosophers == 1)
		return (handle_one_philo(&data, forks, philos));
	if (!create_threads(&data, philos, &monitor_thread, forks))
		return (1);
	join_threads(&data, philos, monitor_thread);
	free_and_cleanup(&data, forks, philos, NULL);
	return (0);
}
