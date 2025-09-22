/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsalette <rsalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 23:54:02 by rsalette          #+#    #+#             */
/*   Updated: 2025/08/15 18:38:40 by rsalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static	int	ft_numstrlen(const char *str)
{
	int	n;

	n = 0;
	while (*str && (*str >= '0' && *str <= '9'))
	{
		n++;
		str++;
	}
	return (n);
}

static	int	ft_power(int rad, int exp)
{
	if (exp == 0)
		return (1);
	if (exp < 0)
		return (1 / ft_power(rad, -exp));
	return (ft_power(rad, exp - 1) * rad);
}

static	int	ft_result(const char *ptr)
{
	int	len;
	int	res;
	int	prog;

	prog = 1;
	res = 0;
	len = ft_numstrlen(ptr);
	while (*ptr >= '0' && *ptr <= '9')
	{
		if (len - prog == 0 || *ptr == 0)
			res = (*ptr - '0') + res;
		else
			res = (*ptr - '0') * ft_power(10, (len - prog)) + res;
		ptr++;
		prog++;
	}
	return (res);
}

int	ft_atoi(const char *ptr)
{
	int	sign;

	sign = 1;
	while (*ptr == 32 || *ptr == 9 || *ptr == 10
		|| *ptr == 13 || *ptr == 11 || *ptr == 12)
		ptr++;
	if (*ptr == '-' || *ptr == '+')
	{
		if (*ptr == '-')
			sign = -sign;
		ptr++;
	}
	if (!(*ptr >= '0' && *ptr <= '9'))
		return (0);
	return (ft_result(ptr) * sign);
}
