/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygomes-d <ygomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 14:38:23 by ygomes-d          #+#    #+#             */
/*   Updated: 2021/11/01 10:50:48 by ygomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_flags(const char *str, int i, t_flags *flag)
{
	char	*check;
	int		j;

	j = -1;
	check = "udicspxX%";
	while (str[i] != check[++j])
	{
		while (check_case(str[i], flag))
			i++;
		if (ft_isdigit(str[i]) || str[i] == '.')
			i = check_dotwdt(str, i, flag);
		if (str[i] == '#')
		{
			flag->hash = 1;
			i++;
		}
	}
	check_conversion_case(flag, str, i);
	return (i);
}

t_flags	*init_flags(t_flags *flag)
{
	flag->wdt = 0;
	flag->zero = 0;
	flag->dot = 0;
	flag->dash = 0;
	flag->sign = 0;
	flag->space = 0;
	flag->hash = 0;
	flag->flen = 0;
	flag->nbrlen = 0;
	flag->prc = 0;
	flag->newprc = 0;
	return (flag);
}

t_flags	*reinit_flags(t_flags *flag)
{
	flag->wdt = 0;
	flag->zero = 0;
	flag->dot = 0;
	flag->dash = 0;
	flag->sign = 0;
	flag->space = 0;
	flag->hash = 0;
	flag->nbrlen = 0;
	flag->prc = 0;
	flag->newprc = 0;
	return (flag);
}
