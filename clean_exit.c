/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaid <mazaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 23:05:11 by mazaid            #+#    #+#             */
/*   Updated: 2025/06/12 15:52:57 by mazaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_and_cleanup(t_data *data, t_fork *forks,
	t_philosopher *philos, const char *msg)
{
	int	i;

	if (msg)
		printf("%s\n", msg);
	if (forks && data)	
	{
		i = 0;
		while (i < data->num_philosophers)
			pthread_mutex_destroy(&forks[i++].mutex);
	}
	if (data)
	{
		pthread_mutex_destroy(&data->print_mutex);
		pthread_mutex_destroy(&data->death_mutex);
		pthread_mutex_destroy(&data->eat_mutex);
	}
	if (philos)
		free(philos);
	if (forks)
		free(forks);
}
