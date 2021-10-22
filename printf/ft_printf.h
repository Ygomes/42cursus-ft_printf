/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygomes-d <ygomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 08:36:47 by ygomes-d          #+#    #+#             */
/*   Updated: 2021/10/22 10:25:50 by ygomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdarg.h>
#include "libft/libft.h"

# define HEXALOW "0123456789abcdef"
# define HEXAUP "0123456789ABCDEF"

typedef struct s_flags
{
	va_list args;
	int wdt;
	int prs;
	int zero;
	int dot;
	int dash;
	int sign;
	int space;
}	t_flags;

int	ft_printf(const char *str, ...);

#endif
