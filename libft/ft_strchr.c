/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygomes-d <ygomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 11:29:05 by ygomes-d          #+#    #+#             */
/*   Updated: 2021/09/12 19:12:41 by ygomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char			*str;
	unsigned char	compare;

	str = (char *)s;
	compare = (unsigned char)c;
	while (*str)
	{
		if (*str == compare)
			return (str);
		str++;
	}
	if (!compare && !*str)
		return (str);
	return (NULL);
}
