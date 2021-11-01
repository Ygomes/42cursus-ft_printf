/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_up.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygomes-d <ygomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 15:19:06 by ygomes-d          #+#    #+#             */
/*   Updated: 2021/11/01 10:27:55 by ygomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_u(unsigned int nbr, t_flags *flag)
{
	flag->nbrlen = get_unbrlen(nbr);
	if (flag->dot)
		treat_dot_flag_upxx(nbr, flag);
	if (!flag->dash && flag->wdt)
		treat_flag(flag, flag->prc, flag->nbrlen);
	if (flag->dot && nbr == 0 && flag->prc == 0)
		treat_flag(flag, 0, 0);
	else
	{
		ft_putunbr_fd(nbr, 1);
		flag->flen += flag->nbrlen;
	}
	if (flag->dash)
		treat_dash_flag(nbr, flag);
	reinit_flags(flag);
}

void	print_hexa(unsigned int i, t_flags *flag)
{
	if (i >= 16)
	{
		print_hexa(i / 16, flag);
		print_hexa(i % 16, flag);
	}
	else
		ft_putchar_fd(HEXALOW[i], 1);
}

void	print_hexap(unsigned long i)
{
	if (i >= 16)
	{
		print_hexap(i / 16);
		print_hexap(i % 16);
	}
	else
		ft_putchar_fd(HEXALOW[i], 1);
}

void	print_p(unsigned long nbr, t_flags *flag)
{
	flag->nbrlen = get_hexaplonglen(nbr);
	flag->nbrlen += 2;
	if (!flag->dash && flag->wdt)
		treat_flag(flag, flag->prc, flag->nbrlen);
	ft_putstr_fd("0x", 1);
	print_hexap(nbr);
	flag->flen += flag->nbrlen;
	if (flag->dash && flag->wdt)
		treat_flag(flag, flag->prc, flag->nbrlen);
	reinit_flags(flag);
}
