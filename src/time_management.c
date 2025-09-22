/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsalette <rsalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:41:38 by rsalette          #+#    #+#             */
/*   Updated: 2025/09/14 16:58:58 by rsalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// returns current_time_from_start in ms
long	get_time_from_start(long start_time)
{
	return (get_current_time() - start_time);
}

// returns absolute current_time in ms
long	get_current_time(void)
{
	struct timeval	tv;
	long			curr_time;

	gettimeofday(&tv, NULL);
	curr_time = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (curr_time);
}

// void wait_for_start(t_data *data)
// {
// 	long now;

// 	now = get_current_time();
// 	while (now < data->start_time)
// 	{
// 		usleep(100);
// 		now = get_current_time();
// 	}
// }

// void philo_runtime_init(t_philo *philo)
// {
// 	wait_for_start(philo->data);
// 	pthread_mutex_lock(&philo->meal_data_mutex);
// 	philo->last_meal = get_current_time();
// 	pthread_mutex_unlock(&philo->meal_data_mutex);
// }
