/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygomes-d <ygomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 14:46:48 by ygomes-d          #+#    #+#             */
/*   Updated: 2021/11/01 10:02:43 by ygomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_c(int chr, t_flags *flag)
{
	if (flag->zero)
		flag->zero = 0;
	if (flag->wdt && !flag->dash)
		treat_flag(flag, flag->prc, 1);
	ft_putchar_fd(chr, 1);
	if (flag->dash && flag->wdt)
		treat_flag(flag, flag->prc, 1);
	flag->flen += 1;
	reinit_flags(flag);
}

void	print_s(char *str, t_flags *flag)
{
	char	*newstr;

	if (!str)
		str = "(null)";
	flag->nbrlen = ft_strlen(str);
	newstr = malloc(sizeof(char) * (flag->nbrlen + 1));
	if (!newstr)
		free(newstr);
	if (flag->wdt && !flag->dash && !flag->dot)
		treat_flag(flag, flag->prc, flag->nbrlen);
	if (flag->dot)
	{
		flag->nbrlen = strlcpydstlen(newstr, str, flag->prc + 1);
		ft_putstr_fd(newstr, 1);
		if (flag->dash)
			treat_flag(flag, flag->newprc, flag->nbrlen);
	}
	else
		ft_putstr_fd(str, 1);
	if (flag->dash && flag->wdt && !flag->dot)
		treat_flag(flag, flag->prc, flag->nbrlen);
	flag->flen += flag->nbrlen;
	free(newstr);
	reinit_flags(flag);
}
