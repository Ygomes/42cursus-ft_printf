/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygomes-d <ygomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 13:30:33 by ygomes-d          #+#    #+#             */
/*   Updated: 2021/09/12 17:00:01 by ygomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	lens1;
	size_t	lens2;
	char	*str;

	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (!str)
		return (NULL);
	while (lens1--)
		str[lens1] = s1[lens1];
	lens1 = ft_strlen(s1);
	while (lens2--)
		str[lens1 + lens2] = s2[lens2];
	lens2 = ft_strlen(s2);
	str[lens1 + lens2] = '\0';
	return (str);
}
