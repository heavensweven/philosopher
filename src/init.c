/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsalette <rsalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:16:50 by rsalette          #+#    #+#             */
/*   Updated: 2025/09/13 20:44:33 by rsalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	data_initializer(int argc, char **argv, t_data *data)
{
	if (!data)
		return (error_print("Data malloc failed.\n"), EXIT_FAILURE);
	data->start_time = -1;
	memset(data->error_string, '\0', sizeof(data->error_string));
	if (arg_management(argc, argv, data) != EXIT_SUCCESS)
		return (ft_strlcat(data->error_string, "Invalid arguments.\n",
				sizeof(data->error_string)), EXIT_FAILURE);
	if (fork_initializer(data) != EXIT_SUCCESS)
	{
		ft_strlcat(data->error_string, "Fork creation failed.", \
			sizeof(data->error_string));
		return (EXIT_FAILURE);
	}
	if (philo_initializer(data) != EXIT_SUCCESS)
	{
		ft_strlcat(data->error_string, "Philo creation failed.", \
			sizeof(data->error_string));
		return (EXIT_FAILURE);
	}
	data->stop = FALSE;
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->stop_mutex, NULL);
	return (EXIT_SUCCESS);
}

t_fork	create_fork(int counter)
{
	t_fork	new_fork;

	new_fork.fork_id = counter;
	pthread_mutex_init(&new_fork.fork_mutex, NULL);
	return (new_fork);
}

int	fork_initializer(t_data *data)
{
	int	f_count;

	f_count = 0;
	data->fork = malloc(sizeof(t_fork) * data->param.nb_philo);
	if (!data->fork)
	{
		ft_strlcat(data->error_string, "Malloc failed. ", \
			sizeof(data->error_string));
		return (EXIT_FAILURE);
	}
	while (f_count < data->param.nb_philo)
	{
		data->fork[f_count] = create_fork(f_count);
		f_count++;
	}
	data->fork_alloc = TRUE;
	return (EXIT_SUCCESS);
}

t_philo	create_philo(int counter, t_data *data)
{
	t_philo	philo;

	philo.philo_id = counter + 1;
	philo.state = THINKING;
	philo.meal_count = 0;
	philo.last_meal = -1;
	pthread_mutex_init(&philo.meal_data_mutex, NULL);
	philo.left_fork = &data->fork[counter];
	philo.right_fork = &data->fork[(counter + 1) % data->param.nb_philo];
	philo.data = data;
	return (philo);
}

int	philo_initializer(t_data *data)
{
	int	ph_count;

	ph_count = 0;
	data->philo = malloc(sizeof(t_philo) * data->param.nb_philo);
	if (!data->philo)
	{
		ft_strlcat(data->error_string, "Malloc failed. ", \
			sizeof(data->error_string));
		return (EXIT_FAILURE);
	}
	while (ph_count < data->param.nb_philo)
	{
		data->philo[ph_count] = create_philo(ph_count, data);
		ph_count++;
	}
	data->philo_alloc = TRUE;
	return (EXIT_SUCCESS);
}
