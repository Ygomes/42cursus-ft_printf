/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygomes-d <ygomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 09:00:45 by ygomes-d          #+#    #+#             */
/*   Updated: 2021/09/11 13:23:22 by ygomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*psrc;
	unsigned char	*pdest;
	size_t			i;

	psrc = (unsigned char *)src;
	pdest = (unsigned char *)dest;
	i = 0;
	if (!psrc && !pdest)
		return (0);
	while (i < n)
	{
		pdest[i] = psrc[i];
		i++;
	}
	return (dest);
}
