/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygomes-d <ygomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 14:19:35 by ygomes-d          #+#    #+#             */
/*   Updated: 2021/09/15 10:30:40 by ygomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	first;
	size_t	last;
	char	*str;

	first = 0;
	last = ft_strlen(s1);
	if (!s1)
		return (0);
	while (s1[first] && ft_strchr(set, s1[first]))
		first++;
	while ((s1[last - 1] && ft_strchr(set, s1[last - 1])) && last >= first)
		last--;
	str = ft_substr(s1, first, last - first);
	if (!str)
		return (NULL);
	return (str);
}
