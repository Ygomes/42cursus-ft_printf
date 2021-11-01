/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_case_conversion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygomes-d <ygomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 12:42:02 by ygomes-d          #+#    #+#             */
/*   Updated: 2021/11/01 10:12:26 by ygomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_case(char c, t_flags *flag)
{
	if (c == '0')
	{
		flag->zero = 1;
		return (1);
	}
	else if (c == '+')
	{
		flag->sign = 1;
		return (1);
	}
	else if (c == '-')
	{
		flag->dash = 1;
		return (1);
	}
	else if (c == ' ')
	{
		flag->space = 1;
		return (1);
	}
	else
		return (0);
}

int	check_dotwdt(const char *str, int i, t_flags *flag)
{
	if (ft_isdigit(str[i]))
	{
		flag->prc = check_w(str, i);
		flag->wdt = 1;
		i += get_nbrlen(flag->prc);
	}
	if (str[i] == '.')
	{
		flag->dot = 1;
		i++;
		while (str[i] == '0')
		{
			flag->zero = 0;
			i++;
		}
		if (check_udicpxx(str, i))
			flag->zero = 0;
		flag->newprc = flag->prc;
		flag->prc = check_w(str, i);
	}
	return (i);
}

int	check_udicpxx(const char *str, int i)
{
	if (str[i] == 'u')
		return (1);
	else if (str[i] == 'd')
		return (1);
	else if (str[i] == 'i')
		return (1);
	else if (str[i] == 'c')
		return (1);
	else if (str[i] == 'p')
		return (1);
	else if (str[i] == 'x')
		return (1);
	else if (str[i] == 'X')
		return (1);
	else
		return (0);
}

int	check_w(const char *str, int i)
{
	int	len;

	len = 0;
	while (ft_isdigit(str[i]))
	{
		len = (len * 10) + (str[i] - 48);
		i++;
	}
	return (len);
}

int	check_conversion_case(t_flags *flag, const char *str, int i)
{
	if (flag->dash && flag->zero)
		flag->zero = 0;
	if (str[i] == 'c')
		print_c(va_arg(flag->args, int), flag);
	if (str[i] == 's')
		print_s(va_arg(flag->args, char *), flag);
	if (str[i] == 'd' || str[i] == 'i')
		print_di(va_arg(flag->args, int), flag);
	if (str[i] == 'u')
		print_u(va_arg(flag->args, unsigned int), flag);
	if (str[i] == 'p')
		print_p(va_arg(flag->args, unsigned long), flag);
	if (str[i] == 'x')
		print_x(va_arg(flag->args, unsigned int), flag);
	if (str[i] == 'X')
		print_xup(va_arg(flag->args, unsigned int), flag);
	if (str[i] == '%')
	{
		ft_putchar_fd('%', 1);
		flag->flen++;
	}
	return (i);
}
