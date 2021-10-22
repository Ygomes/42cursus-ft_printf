/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygomes-d <ygomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 16:22:39 by ygomes-d          #+#    #+#             */
/*   Updated: 2021/09/12 19:08:14 by ygomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_len(unsigned int n)
{
	unsigned int	i;
	unsigned int	nbr;

	i = 0;
	nbr = n;
	while (nbr)
	{
		i++;
		nbr = nbr / 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	unsigned int	num;
	unsigned int	len;
	char			*result;

	num = n;
	if (n < 0)
		num *= -1;
	len = ft_len(num);
	if (n <= 0)
		len++;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	while (len--)
	{
		result[len] = num % 10 + 48;
		num = num / 10;
	}
	if (n < 0)
		result[0] = '-';
	return (result);
}
