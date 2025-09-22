/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsalette <rsalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:15:23 by rsalette          #+#    #+#             */
/*   Updated: 2025/09/13 20:48:08 by rsalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	i;

	i = 0;
	dup = malloc(sizeof(char) * ft_strlen_ultimate(s) + 1);
	if (!dup)
		return (NULL);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	array = malloc(nmemb * size);
	if (!array)
		return (NULL);
	memset(array, 0, nmemb * size);
	return (array);
}

size_t	ft_strlen_ultimate(const char *str)
{
	int	n;

	n = 0;
	if (str == NULL)
		return (0);
	while (str[n])
		n++;
	return (n);
}

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	n;
	size_t	j;

	i = 0;
	j = 0;
	n = ft_strlen_ultimate(dst);
	if (siz <= n)
		return (ft_strlen_ultimate(src) + ft_min(siz, n));
	i = n;
	while (i < (siz - 1) && src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (ft_strlen_ultimate(src) + ft_min(siz, n));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	substr_len;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen_ultimate(s) || len == 0)
	{
		str = malloc(1);
		if (!str)
			return (NULL);
		return (str[0] = '\0', str);
	}
	substr_len = ft_min(len, ft_strlen_ultimate(s) - start);
	str = malloc(substr_len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < substr_len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
