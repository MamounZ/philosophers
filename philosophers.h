/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaid <mazaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:52:48 by mazaid            #+#    #+#             */
/*   Updated: 2025/06/11 23:49:21 by mazaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_data
{
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	int				dead;
	long			start_time;

	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	eat_mutex;
}	t_data;

typedef struct s_philosopher
{
	int			id;
	long		last_meal;
	int			meals_eaten;
	pthread_t	thread;

	t_fork		*left_fork;
	t_fork		*right_fork;
	t_data		*data;
}	t_philosopher;

void	free_and_cleanup(t_data *data, t_fork *forks,
			t_philosopher *philos, const char *msg);
int		ft_atoi(const char *str);
int		validate_args(int argc, char **argv);
int		init_forks_mutexes(t_data *data, t_fork *forks, t_philosopher *philos);
void	init_philosophers(t_data *data, t_fork *forks, t_philosopher *philos);
int		create_threads(t_data *data, t_philosopher *philos,
			pthread_t *monitor_thread, t_fork *forks);
void	join_threads(t_data *data, t_philosopher *philos,
			pthread_t monitor_thread);
int		handle_one_philo(t_data *data, t_fork *forks, t_philosopher *philos);
void	init_data(t_data *data, int argc, char **argv);
void	*monitor(void *arg);
void	*philosopher_routine(void *arg);
long	get_time(void);
void	smart_sleep(long duration, t_data *data);
void	print_action(t_data *data, int id, const char *action);

#endif