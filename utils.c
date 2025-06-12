/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaid <mazaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 23:07:44 by mazaid            #+#    #+#             */
/*   Updated: 2025/06/11 23:52:20 by mazaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	smart_sleep(long duration, t_data *data)
{
	long	start;

	start = get_time();
	while (get_time() - start < duration)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->dead)
		{
			pthread_mutex_unlock(&data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->death_mutex);
		usleep(500);
	}
}

void	print_action(t_data *data, int id, const char *action)
{
	pthread_mutex_lock(&data->death_mutex);
	pthread_mutex_lock(&data->print_mutex);
	if (!data->dead)
		printf("%ld %d %s\n", get_time() - data->start_time, id + 1, action);
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_unlock(&data->death_mutex);
}
