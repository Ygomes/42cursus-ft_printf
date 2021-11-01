/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygomes-d <ygomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 10:01:05 by ygomes-d          #+#    #+#             */
/*   Updated: 2021/09/13 10:16:23 by ygomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	substr_count(char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (*s)
	{
		if (*s != c && j == 0)
		{
			j = 1;
			i++;
		}
		else if (*s == c)
			j = 0;
		s++;
	}
	return (i);
}

static size_t	getlen(char const *str, char c)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			len++;
		if (str[i] == c || !(str[i]))
			return (len);
		i++;
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	**str;
	size_t	start;
	size_t	j;
	size_t	s_len;

	str = (char **)malloc(sizeof(char *) * (substr_count(s, c) + 1));
	if (!str || !s)
		return (NULL);
	i = -1;
	start = 0;
	j = 0;
	s_len = ft_strlen(s) - 1;
	while (s[++i])
	{
		if (s[i] == c || i == s_len)
		{
			if (getlen(s + start, c) > 0)
				str[j++] = ft_substr(s, start, getlen(s + start, c));
			start = i + 1;
		}
	}
	str[j] = 0;
	return (str);
}
