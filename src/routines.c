/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsalette <rsalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:47:01 by rsalette          #+#    #+#             */
/*   Updated: 2025/09/14 16:29:48 by rsalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	eating(t_philo *philo)
{
	if (philo->left_fork == philo->right_fork)
	{
		pthread_mutex_lock(&philo->left_fork->fork_mutex);
		print_fork(philo);
		usleep(philo->data->param.time_to_die);
		pthread_mutex_unlock(&philo->left_fork->fork_mutex);
		return (EXIT_FAILURE);
	}
	if (fork_holding(philo))
		return (EXIT_FAILURE);
	if (!check_stop(philo))
	{
		philo->state = EATING;
		print_state(philo);
		pthread_mutex_lock(&philo->meal_data_mutex);
		philo->last_meal = get_current_time();
		philo->meal_count++;
		pthread_mutex_unlock(&philo->meal_data_mutex);
		if (smart_usleep(philo, philo->data->param.time_to_eat))
			return (unlock_forks(philo), EXIT_FAILURE);
	}
	unlock_forks(philo);
	return (EXIT_SUCCESS);
}

int	sleeping(t_philo *philo)
{
	philo->state = SLEEPING;
	print_state(philo);
	if (smart_usleep(philo, philo->data->param.time_to_sleep))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	thinking(t_philo *philo)
{
	int	duration;

	duration = (int)ft_abs(philo->data->param.time_to_sleep
			- philo->data->param.time_to_eat) + 1;
	philo->state = THINKING;
	print_state(philo);
	if (smart_usleep(philo, duration))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	default_philo_routine(t_philo *philo)
{
	if (eating(philo))
		return (EXIT_FAILURE);
	if (check_stop(philo))
		return (EXIT_FAILURE);
	if (sleeping(philo))
		return (EXIT_FAILURE);
	if (check_stop(philo))
		return (EXIT_FAILURE);
	if (thinking(philo))
		return (EXIT_FAILURE);
	if (check_stop(philo))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
