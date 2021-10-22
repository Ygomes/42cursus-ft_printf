/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygomes-d <ygomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 09:58:36 by ygomes-d          #+#    #+#             */
/*   Updated: 2021/09/11 13:21:33 by ygomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*psrc;
	unsigned char	*pdest;

	psrc = (unsigned char *)src;
	pdest = (unsigned char *)dest;
	if (!psrc && !pdest)
		return (NULL);
	if (psrc < pdest)
		while (n--)
			pdest[n] = psrc[n];
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
