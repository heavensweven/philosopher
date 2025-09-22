/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_close_management_0.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsalette <rsalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:47:41 by rsalette          #+#    #+#             */
/*   Updated: 2025/09/14 16:14:17 by rsalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	free_philo(t_data *data)
{
	free(data->philo);
	data->philo_alloc = FALSE;
}

void	free_fork(t_data *data)
{
	free (data->fork);
	data->fork_alloc = FALSE;
}

void	memory_liberator(t_data *data)
{
	if (data)
	{
		if (data->philo_alloc == TRUE)
			free_philo(data);
		if (data->fork_alloc == TRUE)
			free_fork(data);
		error_print(data->error_string);
		printf("Memory liberated.\n");
	}
}

void	free_args(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
}

void	error_print(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
}
