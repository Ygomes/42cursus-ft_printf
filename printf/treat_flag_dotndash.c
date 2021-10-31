/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_flag_dotndash.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygomes-d <ygomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 11:46:17 by ygomes-d          #+#    #+#             */
/*   Updated: 2021/10/31 14:46:12 by ygomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	treat_dot_flag_di(int nbr, t_flags *flag)
{
	if (nbr < 0)
		flag->prc++;
	if (flag->newprc > flag->prc)
	{
		flag->zero = 0;
		if(!flag->dash && flag->prc > flag->nbrlen)
			treat_flag(flag, flag->newprc, flag->prc);
		if(!flag->dash && flag->prc <= flag->nbrlen && nbr != 0)
			treat_flag(flag, flag->newprc, flag->nbrlen);
		if(!flag->dash && flag->prc <= flag->nbrlen && nbr == 0)
			treat_flag(flag, flag->newprc, 0);
	}
	if (nbr < 0)
		ft_putchar_fd('-', 1);
	if (flag->prc > flag->nbrlen)
	{
		flag->zero = 1;
		if (flag->dash)
			treat_flag(flag, flag->prc, flag->nbrlen);
	}
}

void	treat_dot_flag_upxX(unsigned int nbr, t_flags *flag)
{
	if (flag->newprc > flag->prc)
	{
		flag->zero = 0;
		if(!flag->dash && flag->prc > flag->nbrlen)
			treat_flag(flag, flag->newprc, flag->prc);
		if(!flag->dash && flag->prc <= flag->nbrlen && nbr != 0)
			treat_flag(flag, flag->newprc, flag->nbrlen);
		if(!flag->dash && flag->prc <= flag->nbrlen && nbr == 0)
			treat_flag(flag, flag->newprc, 0);
	}
	if (flag->prc > flag->nbrlen)
	{
		flag->zero = 1;
		if (flag->dash)
			treat_flag(flag, flag->prc, flag->nbrlen);
	}
}

void treat_dash_flag(unsigned int nbr, t_flags *flag)
{
	if (flag->newprc > flag->prc && flag->prc > flag->nbrlen)
		flag->zero = 0;
	if (flag->prc < flag->newprc && flag->prc <= flag->nbrlen && nbr != 0)
		treat_flag(flag, flag->newprc, flag->nbrlen);
	if (flag->prc < flag->newprc && flag->prc <= flag->nbrlen && nbr == 0)
		treat_flag(flag, flag->newprc, 0);
	if (flag->newprc > flag->prc && flag->prc > flag->nbrlen)
		treat_flag(flag, flag->newprc, flag->prc);
	if (!flag->dot)
		treat_flag(flag, flag->prc, flag->nbrlen);
}
