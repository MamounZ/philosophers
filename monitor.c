/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaid <mazaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 23:13:44 by mazaid            #+#    #+#             */
/*   Updated: 2025/06/12 15:13:29 by mazaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_philo_death(t_philosopher *philos, t_data *data, int i)
{
	if (get_time() - philos[i].last_meal > data->time_to_die)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->dead = 1;
		pthread_mutex_lock(&data->print_mutex);
		printf("%ld %d has died\n", get_time()
			- data->start_time, philos[i].id + 1);
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(&data->death_mutex);
		pthread_mutex_unlock(&data->eat_mutex);
		return (1);
	}
	return (0);
}

int	check_meals(t_philosopher *philos, t_data *data, int *done)
{
	int	i;

	i = -1;
	while (++i < data->num_philosophers)
	{
		pthread_mutex_lock(&data->eat_mutex);
		if (data->max_meals == -1 || philos[i].meals_eaten < data->max_meals)
			*done = 0;
		if (check_philo_death(philos, data, i))
			return (1);
		pthread_mutex_unlock(&data->eat_mutex);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_philosopher	*philos;
	t_data			*data;
	int				done;

	philos = (t_philosopher *)arg;
	data = philos[0].data;
	while (1)
	{
		done = 1;
		if (check_meals(philos, data, &done))
			return (NULL);
		if (data->max_meals != -1 && done)
			return (NULL);
		usleep(10);
	}
}
