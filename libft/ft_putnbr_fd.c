/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygomes-d <ygomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 10:49:50 by ygomes-d          #+#    #+#             */
/*   Updated: 2021/09/12 16:32:52 by ygomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	div;
	unsigned int	result;
	unsigned int	nbr;

	nbr = n;
	div = 1;
	if (n < 0)
	{
		nbr = nbr * -1;
		write (fd, "-", 1);
	}
	while (div <= nbr / 10)
		div = div * 10;
	while (div > 0)
	{
		result = nbr / div + 48;
		nbr = nbr % div;
		div = div / 10;
		write (fd, &result, 1);
	}
}
