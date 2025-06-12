/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaid <mazaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 23:09:35 by mazaid            #+#    #+#             */
/*   Updated: 2025/06/12 15:13:16 by mazaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		print_action(philo->data, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork->mutex);
		print_action(philo->data, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		print_action(philo->data, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->left_fork->mutex);
		print_action(philo->data, philo->id, "has taken a fork");
	}
}

void	release_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(&philo->right_fork->mutex);
	pthread_mutex_unlock(&philo->left_fork->mutex);
}

int	should_stop_philosopher(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->death_mutex);
	stop = data->dead;
	pthread_mutex_unlock(&data->death_mutex);
	return (stop);
}

void	philo_eat(t_philosopher *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->eat_mutex);
	philo->last_meal = get_time();
	print_action(data, philo->id, "is eating");
	philo->meals_eaten++;
	pthread_mutex_unlock(&data->eat_mutex);
	smart_sleep(data->time_to_eat, data);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;
	t_data			*data;

	philo = (t_philosopher *)arg;
	data = philo->data;
	if (philo->id % 2 != 0)
		usleep(200);
	while (1)
	{
		if (should_stop_philosopher(data))
			break ;
		take_forks(philo);
		philo_eat(philo);
		release_forks(philo);
		if (data->max_meals != -1 && philo->meals_eaten >= data->max_meals)
			break ;
		print_action(data, philo->id, "is sleeping");
		smart_sleep(data->time_to_sleep, data);
		print_action(data, philo->id, "is thinking");
		usleep(1000);
	}
	return (NULL);
}
