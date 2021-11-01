/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygomes-d <ygomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 14:48:10 by ygomes-d          #+#    #+#             */
/*   Updated: 2021/11/01 10:07:33 by ygomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	treat_flag(t_flags *flag, int count, int len)
{
	if (flag->sign)
		len++;
	while (count - len > 0)
	{
		if (flag->zero)
			ft_putnbr_fd(0, 1);
		else
			ft_putchar_fd(' ', 1);
		count--;
		flag->flen++;
	}
}

void	treat_space(t_flags *flag)
{
	ft_putchar_fd(' ', 1);
	flag->flen++;
}

void	treat_sign(t_flags *flag)
{
	ft_putchar_fd('+', 1);
	flag->flen++;
}

int	treat_neg(int nbr)
{
	nbr *= -1;
	ft_putchar_fd('-', 1);
	return (nbr);
}
