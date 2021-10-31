/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_di.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygomes-d <ygomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 14:50:22 by ygomes-d          #+#    #+#             */
/*   Updated: 2021/10/31 15:02:21 by ygomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_di(int nbr, t_flags *flag)
{
	int number;

	number = nbr;
	flag->nbrlen = get_nbrlen(nbr);
	if (nbr < -2147483647)
		flag->nbrlen = 11;
	if (nbr < 0 && flag->dot)
		number *= -1;
	if (flag->dot)
		treat_dot_flag_di(nbr, flag);
	if (nbr < 0 && !flag->dot && flag->zero)
		number = treat_neg(nbr);
	if (!flag->dash && flag->wdt)
		treat_flag(flag, flag->prc, flag->nbrlen);
	if (flag->space && !flag->wdt && nbr >= 0)
		treat_space(flag);
	if (nbr < 0 && !flag->dot && !flag->zero)
		number = treat_neg(nbr);
	if (flag->sign && nbr >= 0)
		treat_sign(flag);
	print_number_di(nbr, flag, number);
	if (flag->dash)
		treat_dash_flag(nbr, flag);
	reinit_flags(flag);
}

void	print_number_di(int nbr, t_flags *flag, int number)
{
	if (flag->dot && nbr == 0 && flag->prc == 0)
		treat_flag(flag, 0, 0);
	else if (nbr < -2147483647)
	{
		put_long_nbr(nbr);
		flag->flen += flag->nbrlen;
	}
	else
	{
		ft_putnbr_fd(number, 1);
		flag->flen += flag->nbrlen;
	}
}

void	put_long_nbr(int n)
{
	long int	nbr;

	nbr = (long int)n * - 1;
	ft_putlongnbr_fd(nbr, 1);
}

void	ft_putunbr_fd(unsigned int n, int fd)
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

void	ft_putlongnbr_fd(long int n, int fd)
{
	long int	div;
	long int	result;
	long int	nbr;

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
