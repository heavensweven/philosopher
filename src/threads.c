/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsalette <rsalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:44:40 by rsalette          #+#    #+#             */
/*   Updated: 2025/09/14 16:42:01 by rsalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*watchdog_thread_ft(void *arg)
{
	t_watchdog_args	*wd_args;
	t_bool			stop_on;

	wd_args = (t_watchdog_args *)arg;
	usleep(100);
	while (1)
	{
		pthread_mutex_lock(&wd_args->data->stop_mutex);
		stop_on = wd_args->data->stop;
		pthread_mutex_unlock(&wd_args->data->stop_mutex);
		stop_on = watchdog_check_loop(wd_args);
		if (stop_on)
			break ;
		usleep(100);
	}
	free(wd_args);
	return (NULL);
}

int	watchdog_check_loop(t_watchdog_args	*wd_args)
{
	int	i;

	i = 0;
	wd_args->full_philo_count = 0;
	while ((i < wd_args->nb_philo))
	{
		if (death_management(&wd_args->data->philo[i],
				wd_args->time_to_die))
			return (1);
		if (wd_args->must_eat >= 0)
			if (eat_limit_management(&wd_args->data->philo[i], wd_args))
				return (1);
		i++;
	}
	return (0);
}

void	*philo_thread_ft(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->meal_data_mutex);
	philo->last_meal = philo->data->start_time;
	pthread_mutex_unlock(&philo->meal_data_mutex);
	if (philo->philo_id % 2 == 0)
		smart_usleep(philo, philo->data->param.time_to_eat / 2);
	while (1)
	{
		if (default_philo_routine(philo) == EXIT_FAILURE)
			break ;
	}
	return (NULL);
}
