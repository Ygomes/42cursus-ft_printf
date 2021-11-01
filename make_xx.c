/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_xx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygomes-d <ygomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 15:21:29 by ygomes-d          #+#    #+#             */
/*   Updated: 2021/11/01 10:28:56 by ygomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_x(unsigned int nbr, t_flags *flag)
{
	flag->nbrlen = get_hexaplen(nbr);
	if (flag->hash && nbr > 0)
	{
		ft_putstr_fd("0x", 1);
		flag->flen += 2;
	}
	if (flag->dot)
		treat_dot_flag_upxx(nbr, flag);
	if (!flag->dash && flag->wdt)
		treat_flag(flag, flag->prc, flag->nbrlen);
	if (flag->dot && nbr == 0 && flag->prc == 0)
		treat_flag(flag, 0, 0);
	else
	{
		print_hexa(nbr, flag);
		flag->flen += flag->nbrlen;
	}
	if (flag->dash)
		treat_dash_flag(nbr, flag);
	reinit_flags(flag);
}

void	print_hexaup(unsigned int i, t_flags *flag)
{
	if (i >= 16)
	{
		print_hexaup(i / 16, flag);
		print_hexaup(i % 16, flag);
	}
	else
	{
		ft_putchar_fd(HEXAUP[i], 1);
	}
}

void	print_xup(unsigned int nbr, t_flags *flag)
{
	flag->nbrlen = get_hexaplen(nbr);
	if (flag->hash && nbr > 0)
	{
		ft_putstr_fd("0X", 1);
		flag->flen += 2;
	}
	if (flag->dot)
		treat_dot_flag_upxx(nbr, flag);
	if (!flag->dash && flag->wdt)
		treat_flag(flag, flag->prc, flag->nbrlen);
	if (flag->dot && nbr == 0 && flag->prc == 0)
		treat_flag(flag, 0, 0);
	else
	{
		print_hexaup(nbr, flag);
		flag->flen += flag->nbrlen;
	}
	if (flag->dash)
		treat_dash_flag(nbr, flag);
	reinit_flags(flag);
}
