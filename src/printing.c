/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsalette <rsalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:02:25 by rsalette          #+#    #+#             */
/*   Updated: 2025/09/13 20:51:46 by rsalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_state(t_philo *philo)
{
	if (check_stop(philo))
		return ;
	pthread_mutex_lock(&philo->data->print_mutex);
	if (philo->state == THINKING)
		printf("%ld %d is thinking\n",
			get_time_from_start(philo->data->start_time), philo->philo_id);
	else if (philo->state == EATING)
		printf("%ld %d is eating\n",
			get_time_from_start(philo->data->start_time), philo->philo_id);
	else if (philo->state == SLEEPING)
		printf("%ld %d is sleeping\n",
			get_time_from_start(philo->data->start_time), philo->philo_id);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	print_fork(t_philo *philo)
{
	if (check_stop(philo))
		return ;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d has taken a fork\n",
		get_time_from_start(philo->data->start_time), philo->philo_id);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	print_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf(("%ld %d died\n"), get_time_from_start(philo->data->start_time),
		philo->philo_id);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
