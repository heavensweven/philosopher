/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsalette <rsalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:02:20 by rsalette          #+#    #+#             */
/*   Updated: 2025/09/14 19:03:52 by rsalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// smart sleeps duration time in ms.
// returns 1 at time of death if interrupted by death
int	smart_usleep(t_philo *philo, int duration)
{
	long		start;
	long		end;

	start = get_current_time();
	end = start + (long)duration;
	while (get_current_time() < end)
	{
		if (check_stop(philo))
			return (1);
		usleep(100);
	}
	return (0);
}

int	ft_tablen(char **tab)
{
	int	n;

	n = 0;
	while (tab[n])
		n++;
	return (n);
}

size_t	ft_abs(size_t m)
{
	if (m < 0)
		return (-m);
	return (m);
}

size_t	ft_min(size_t n1, size_t n2)
{
	if (n1 <= n2)
		return (n1);
	else
		return (n2);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
