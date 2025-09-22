/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsalette <rsalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:06:19 by rsalette          #+#    #+#             */
/*   Updated: 2025/08/16 17:19:05 by rsalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

unsigned int	ft_countsplit(char const *string, char const find)
{
	size_t	s_count;
	size_t	result;
	int		in_word;

	s_count = 0;
	result = 0;
	in_word = 0;
	while (string[s_count])
	{
		if (string[s_count] != find && in_word == 0)
		{
			in_word = 1;
			result++;
		}
		else if (string[s_count] == find)
			in_word = 0;
		s_count++;
	}
	return (result);
}

unsigned int	ft_splitlen(char const *string, char const find)
{
	size_t	s_count;

	s_count = 0;
	while (string[s_count] && string[s_count] != find)
		s_count++;
	return (s_count);
}

void	ft_antileak(char **arr, int row)
{
	int	i;

	i = row - 1;
	if (!arr)
		return ;
	while (i >= 0)
	{
		if (arr[i])
		{
			free(arr[i]);
			arr[i] = NULL;
		}
		i--;
	}
	free(arr);
	arr = NULL;
}

char	*ft_get_next_word(char const *s, char c, int *i)
{
	char	*substr;
	int		len;

	while (s[*i] && s[*i] == c)
		(*i)++;
	len = ft_splitlen(s + *i, c);
	substr = ft_substr(s, *i, len);
	if (!substr)
		return (NULL);
	*i = *i + len;
	return (substr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;
	int		y;

	if (!s)
		return (NULL);
	i = 0;
	y = 0;
	arr = malloc(sizeof(char *) * (ft_countsplit(s, c) + 1));
	if (!arr)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			arr[y] = ft_get_next_word(s, c, &i);
			if (!arr[y])
				return (ft_antileak(arr, y), NULL);
			y++;
		}
		else
			i++;
	}
	return (arr[y] = NULL, arr);
}

// #include <stdio.h>

// int main ()
// {
// 	char				*s = "4 67 3 87 23";
// 	char				c = ' ';
// 	unsigned int		i = 0;
// 	char				**tab = ft_split(s, c);
// 	while (tab[i])
// 	{
// 		printf("%s\n", tab[i]);
// 		i++;
// 	}
// 	return (0);
// }
