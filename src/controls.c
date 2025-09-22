/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsalette <rsalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:06:55 by rsalette          #+#    #+#             */
/*   Updated: 2025/09/13 20:52:09 by rsalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// Checks, set and print death of philo
int	death_management(t_philo *philo, int time_to_die)
{
	long	last;
	long	now;

	now = get_current_time();
	pthread_mutex_lock(&philo->meal_data_mutex);
	last = philo->last_meal;
	pthread_mutex_unlock(&philo->meal_data_mutex);
	if (last <= 0)
		return (0);
	if ((now - last) > (long)time_to_die)
	{
		pthread_mutex_lock(&philo->data->stop_mutex);
		philo->data->stop = TRUE;
		pthread_mutex_unlock(&philo->data->stop_mutex);
		print_death(philo);
		return (1);
	}
	else
		return (0);
}

// Check and returns stop value
int	check_stop(t_philo *philo)
{
	int	return_value;

	pthread_mutex_lock(&philo->data->stop_mutex);
	if (philo->data->stop == TRUE)
		return_value = 1;
	else
		return_value = 0;
	pthread_mutex_unlock(&philo->data->stop_mutex);
	return (return_value);
}

// If philo ate enough, add +1 to full_philo_count.
// If full_philo_count > must_eat, sets stop ON and returns 1.
int	eat_limit_management(t_philo *philo, t_watchdog_args *wd_args)
{
	pthread_mutex_lock(&philo->meal_data_mutex);
	if (philo->meal_count >= wd_args->must_eat)
		(wd_args->full_philo_count)++;
	pthread_mutex_unlock(&philo->meal_data_mutex);
	if (wd_args->full_philo_count >= wd_args->nb_philo)
	{
		pthread_mutex_lock(&philo->data->stop_mutex);
		philo->data->stop = TRUE;
		pthread_mutex_unlock(&philo->data->stop_mutex);
		return (1);
	}
	return (0);
}
