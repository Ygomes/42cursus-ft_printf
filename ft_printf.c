/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygomes-d <ygomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 19:26:48 by ygomes-d          #+#    #+#             */
/*   Updated: 2021/11/01 10:30:01 by ygomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	int		i;
	int		len;
	t_flags	*flags;

	flags = (t_flags *)malloc(sizeof(t_flags));
	if (!flags)
		return (0);
	va_start(flags->args, str);
	i = -1;
	len = 0;
	init_flags(flags);
	while (str[++i])
	{
		if (str[i] == '%')
			i = check_flags(str, i + 1, flags);
		else
		{
			ft_putchar_fd(str[i], 1);
			flags->flen++;
		}
	}
	len = flags->flen;
	va_end (flags->args);
	free (flags);
	return (len);
}
