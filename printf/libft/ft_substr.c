/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygomes-d <ygomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 12:54:35 by ygomes-d          #+#    #+#             */
/*   Updated: 2021/09/12 19:58:03 by ygomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	j;
	size_t	size;

	if (start > ft_strlen(s))
		return (ft_strdup(""));
	size = ft_strlen(s + start);
	if (size < len)
		len = size;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr || !s)
		return (NULL);
	i = 0;
	j = 0;
	while (i < start)
		i++;
	while (s[i + j] && j < len)
	{
		substr[j] = s[i + j];
		j++;
	}
	substr[j] = '\0';
	return (substr);
}
