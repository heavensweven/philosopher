/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsalette <rsalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:24:28 by rsalette          #+#    #+#             */
/*   Updated: 2025/09/14 16:28:46 by rsalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	fork_holding(t_philo *philo)
{
	t_fork	*first;
	t_fork	*second;

	if (philo->left_fork < philo->right_fork)
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	else
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	pthread_mutex_lock(&first->fork_mutex);
	if (check_stop(philo))
	{
		pthread_mutex_unlock(&first->fork_mutex);
		return (EXIT_FAILURE);
	}
	print_fork(philo);
	pthread_mutex_lock(&second->fork_mutex);
	print_fork(philo);
	return (EXIT_SUCCESS);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->fork_mutex);
	pthread_mutex_unlock(&philo->right_fork->fork_mutex);
}
