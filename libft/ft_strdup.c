/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygomes-d <ygomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 13:12:32 by ygomes-d          #+#    #+#             */
/*   Updated: 2021/09/12 17:00:37 by ygomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dups;

	dups = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	i = 0;
	if (!dups)
		return (NULL);
	while (s[i])
	{
		dups[i] = s[i];
		i++;
	}
	dups[i] = '\0';
	return (dups);
}
