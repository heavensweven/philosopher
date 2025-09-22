/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsalette <rsalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:41:26 by rsalette          #+#    #+#             */
/*   Updated: 2025/09/13 20:54:52 by rsalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	simulation(t_data *data)
{
	data->start_time = get_current_time();
	if (threads_create(data) != EXIT_SUCCESS)
	{
		ft_strlcat(data->error_string, "Threads creation failure.\n", \
			sizeof(data->error_string));
		return (EXIT_FAILURE);
	}
	if (threads_join(data) != EXIT_SUCCESS)
	{
		ft_strlcat(data->error_string, "Threads execution failure.\n", \
			sizeof(data->error_string));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// wd_args holds a link to data and a copy of parameters
int	threads_create(t_data *data)
{
	int				i;
	t_watchdog_args	*wd_args;

	wd_args = malloc(sizeof(t_watchdog_args));
	if (!wd_args)
	{
		ft_strlcat(data->error_string, "WD args malloc failed.\n",
			sizeof(data->error_string));
		return (EXIT_FAILURE);
	}
	wd_args->data = data;
	wd_args->nb_philo = data->param.nb_philo;
	wd_args->time_to_die = data->param.time_to_die;
	wd_args->must_eat = data->param.number_of_times_each_philosopher_must_eat;
	wd_args->full_philo_count = 0;
	i = 0;
	pthread_create(&data->th_watchdog, NULL, watchdog_thread_ft, wd_args);
	while (i < data->param.nb_philo)
	{
		if (pthread_create(&data->philo[i].th_philo, NULL,
				philo_thread_ft, &data->philo[i]) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	threads_join(t_data *data)
{
	int	i;

	i = 0;
	pthread_join(data->th_watchdog, NULL);
	while (i < data->param.nb_philo)
	{
		if (pthread_join(data->philo[i].th_philo, NULL) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data			data;

	if (data_initializer(argc, argv, &data) != EXIT_SUCCESS)
	{
		ft_strlcat(data.error_string, "Initialisation failed.\n",
			sizeof(data.error_string));
		memory_liberator(&data);
		return (EXIT_FAILURE);
	}
	if (simulation(&data) != EXIT_SUCCESS)
	{
		ft_strlcat(data.error_string, "Simulation interrupted.\n",
			sizeof(data.error_string));
		memory_liberator(&data);
		return (EXIT_FAILURE);
	}
	memory_liberator(&data);
	return (EXIT_SUCCESS);
}
