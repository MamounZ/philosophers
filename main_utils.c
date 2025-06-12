/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaid <mazaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 23:15:16 by mazaid            #+#    #+#             */
/*   Updated: 2025/06/11 23:33:02 by mazaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_forks_mutexes(t_data *data, t_fork *forks, t_philosopher *philos)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		if (pthread_mutex_init(&forks[i].mutex, NULL) != 0)
		{
			free_and_cleanup(data, forks, philos,
				"Error: Mutex initialization failed.");
			return (0);
		}
		i++;
	}
	return (1);
}

void	init_philosophers(t_data *data, t_fork *forks, t_philosopher *philos)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		philos[i].id = i;
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % data->num_philosophers];
		philos[i].data = data;
		philos[i].last_meal = data->start_time;
		philos[i].meals_eaten = 0;
		i++;
	}
}

int	create_threads(t_data *data, t_philosopher *philos,
	pthread_t *monitor_thread, t_fork *forks)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		if (pthread_create(&philos[i].thread, NULL,
				philosopher_routine, &philos[i]) != 0)
		{
			free_and_cleanup(data, forks, philos,
				"Error: Thread creation failed.");
			return (0);
		}
		i++;
	}
	if (pthread_create(monitor_thread, NULL, monitor, philos) != 0)
	{
		free_and_cleanup(data, forks, philos,
			"Error: Monitor thread creation failed.");
		return (0);
	}
	return (1);
}

void	join_threads(t_data *data, t_philosopher *philos,
	pthread_t monitor_thread)
{
	int	i;

	i = 0;
	if (pthread_join(monitor_thread, NULL) != 0)
		printf("Warning: Failed to join monitor thread.\n");
	while (i < data->num_philosophers)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			printf("Warning: Failed to join philosopher thread %d.\n", i);
		i++;
	}
}

int	handle_one_philo(t_data *data, t_fork *forks, t_philosopher *philos)
{
	print_action(data, 0, "is thinking");
	print_action(data, 0, "has taken a fork");
	smart_sleep(data->time_to_die, data);
	print_action(data, 0, "has died");
	free_and_cleanup(data, forks, philos, NULL);
	return (0);
}
