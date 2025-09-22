/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsalette <rsalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:56:47 by rsalette          #+#    #+#             */
/*   Updated: 2025/09/14 19:11:50 by rsalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	arg_management(int argc, char **argv, t_data *data)
{
	char	**args;

	args = arg_setter(argc, argv);
	if (args == NULL)
	{
		ft_strlcat(data->error_string, "Malloc failed.\n", \
			sizeof(data->error_string));
		return (EXIT_FAILURE);
	}
	if (ft_tablen(args) < 4 || ft_tablen(args) > 5)
	{
		ft_strlcat(data->error_string, "Number of args invalid.\n", \
			sizeof(data->error_string));
		free_tab(args);
		return (EXIT_FAILURE);
	}
	if (mandatory_arg_dispatch(data, args))
		return (EXIT_FAILURE);
	if (optional_arg_dispatch(data, args))
		return (EXIT_FAILURE);
	free_tab(args);
	return (EXIT_SUCCESS);
}

char	**arg_setter(int argc, char **argv)
{
	char	**result;
	int		i;

	if (argc < 2 || (argc == 2 && !argv[1][0]))
		return (NULL);
	else if (argc == 2)
		result = ft_split(argv[1], ' ');
	else
	{
		result = ft_calloc(argc, sizeof(char *));
		if (!result)
			return (NULL);
		i = 1;
		while (i < argc)
		{
			result[i - 1] = ft_strdup(argv[i]);
			if (!result[i - 1])
				return (free_tab_partial(result, i - 1));
			i++;
		}
	}
	return (result);
}

int	mandatory_arg_dispatch(t_data *data, char	**args)
{
	if (arg_check(args))
	{
		ft_strlcat(data->error_string, "Args must be positive integers.\n", \
			sizeof(data->error_string));
		free_tab(args);
		return (EXIT_FAILURE);
	}
	data->param.nb_philo = ft_atoi(args[0]);
	data->param.time_to_die = ft_atoi(args[1]);
	data->param.time_to_eat = ft_atoi(args[2]);
	data->param.time_to_sleep = ft_atoi(args[3]);
	if (data->param.nb_philo <= 0
		|| data->param.time_to_die <= 0
		|| data->param.time_to_eat <= 0
		|| data->param.time_to_sleep <= 0)
	{
		ft_strlcat(data->error_string, "Args must be > 0.\n", \
			sizeof(data->error_string));
		free_tab(args);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	optional_arg_dispatch(t_data *data, char	**args)
{
	if (ft_tablen(args) == 5)
	{
		data->param.number_of_times_each_philosopher_must_eat
			= ft_atoi(args[4]);
		if (data->param.number_of_times_each_philosopher_must_eat <= 0)
		{
			ft_strlcat(data->error_string, "Eat requirement must be > 0.\n", \
				sizeof(data->error_string));
			free_tab(args);
			return (EXIT_FAILURE);
		}
	}
	else
	{
		data->param.number_of_times_each_philosopher_must_eat = -1;
	}
	return (EXIT_SUCCESS);
}

int	arg_check(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (!ft_isdigit(args[i][j]))
				return (EXIT_FAILURE);
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
