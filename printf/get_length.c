/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_length.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygomes-d <ygomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 12:36:02 by ygomes-d          #+#    #+#             */
/*   Updated: 2021/10/31 12:38:08 by ygomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_nbrlen( int n)
{
	 int	i;
	 int	nbr;

	i = 0;
	nbr = n;
	if (n == 0)
		i = 1;
 	if (nbr < 0)
	{
		nbr *= -1;
		i++;
	}
	while (nbr)
	{
		i++;
		nbr = nbr / 10;
	}
	return (i);
}

unsigned int	get_unbrlen(unsigned int n)
{
	unsigned int	i;
	unsigned int	nbr;

	i = 0;
	nbr = n;
	if (n == 0)
		i = 1;
 	if (nbr < 0)
	{
		nbr *= -1;
		i++;
	}
	while (nbr)
	{
		i++;
		nbr = nbr / 10;
	}
	return (i);
}

int	strlcpydstlen(char *dst, const char *src, int size)
{
	int	i;
	int	len;

	i = 0;
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	len = ft_strlen(dst);
	if (size == 0)
		return (len);
	return (len);
}

int	get_hexaplen(unsigned int i)
{
	int len;

	len = 0;
	if (i == 0)
		len = 1;
	if (i < 0)
	{
		i *= -1;
		len++;
	}
	while (i > 0)
	{
		i = i / 16;
		len ++;
	}
	return (len);
}

int	get_hexaplonglen(unsigned long i)
{
	int len;

	len = 0;
	if (i == 0)
		len = 1;
	if (i < 0)
	{
		i *= -1;
		len++;
	}
	while (i > 0)
	{
		i = i / 16;
		len ++;
	}
	return (len);
}
