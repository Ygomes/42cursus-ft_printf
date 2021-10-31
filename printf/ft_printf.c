/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygomes-d <ygomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 19:26:48 by ygomes-d          #+#    #+#             */
/*   Updated: 2021/10/31 11:43:29 by ygomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_flags	*init_flags(t_flags  *flag)
{
	flag->wdt = 0;
	flag->zero = 0;
	flag->dot = 0;
	flag->dash = 0;
	flag->sign = 0;
	flag->space = 0;
	flag->hash = 0;
	flag->flen= 0;
	flag->nbrlen = 0;
	flag->prc = 0;
	flag->newprc = 0;
	return (flag);
}

t_flags	*reinit_flags(t_flags  *flag)
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

static int	check_w(const char *str, int i)
{
	int len;

	len = 0;
	while (ft_isdigit(str[i]))
	{
		len = (len * 10) + (str[i] - 48);
		i++;
	}
	return (len);
}

static int	check_udicpxX(const char *str, int i)
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

static int	check_case(char c, t_flags *flag)
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

static int	check_dotwdt(const char *str, int i, t_flags *flag)
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
		while(str[i] == '0')
		{
			flag->zero = 0;
			i++;
		}
		if (check_udicpxX(str, i))
			flag->zero = 0;
		flag->newprc = flag->prc;
		flag->prc = check_w(str, i);
	}
	return (i);
}

static int	check_flags(const char *str, int i, t_flags *flag)
{
	char *check;
	int j;

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
	print_char(flag ,str, i);
	return (i);
}

static  int	get_nbrlen( int n)
{
	 int	i;
	 int	nbr;

	i = 0;
	nbr = n;
	if (n == 0)
		i = 1;
 	if (nbr < 0)
	{
		nbr *= -1;
		i++;
	}
	while (nbr)
	{
		i++;
		nbr = nbr / 10;
	}
	return (i);
}

static unsigned int	get_unbrlen(unsigned int n)
{
	unsigned int	i;
	unsigned int	nbr;

	i = 0;
	nbr = n;
	if (n == 0)
		i = 1;
 	if (nbr < 0)
	{
		nbr *= -1;
		i++;
	}
	while (nbr)
	{
		i++;
		nbr = nbr / 10;
	}
	return (i);
}

static void	print_c(int chr, t_flags *flag)
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

static int	strlcpydstlen(char *dst, const char *src, int size)
{
	int	i;
	int	len;

	i = 0;
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	len = ft_strlen(dst);
	if (size == 0)
		return (len);
	return (len);
}

static void	print_s(char *str, t_flags *flag)
{
	char *newstr;
	int  newlen;

	if (!str)
		str = "(null)";
	flag->nbrlen = ft_strlen(str);
	newstr = malloc(sizeof(char) * (flag->nbrlen + 1));
	if (!newstr)
		free(newstr);
	newlen = flag->nbrlen;
	if (flag->zero)
		flag->zero = 0;
	if (flag->wdt && !flag->dash && !flag->dot)
		treat_flag(flag, flag->prc, newlen);
	if (flag->dot)
	{
		newlen = strlcpydstlen(newstr, str, flag->prc + 1);
		ft_putstr_fd(newstr, 1);
		if (flag->dash)
			treat_flag(flag, flag->newprc, newlen);
	}
	else
		ft_putstr_fd(str, 1);
	if (flag->dash && flag->wdt && !flag->dot)
		treat_flag(flag, flag->prc, newlen);
	flag->flen += newlen;
	free(newstr);
	reinit_flags(flag);
}

static void	treat_flag(t_flags *flag ,int count, int len)
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

static void	ft_putlongnbr_fd(long int n, int fd)
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

static void	put_long_nbr(int n)
{
	long int	nbr;

	nbr = (long int)n * - 1;
	ft_putlongnbr_fd(nbr, 1);
}

static void	treat_dot_flag_di(int nbr, t_flags *flag)
{
	if (nbr < 0)
		flag->prc++;
	if (flag->newprc > flag->prc)
	{
		flag->zero = 0;
		if(flag->newprc > flag->prc && !flag->dash && flag->prc > flag->nbrlen)
		treat_flag(flag, flag->newprc, flag->prc);
		if(flag->newprc > flag->prc && !flag->dash && flag->prc <= flag->nbrlen && nbr != 0)
			treat_flag(flag, flag->newprc, flag->nbrlen);
		if(flag->newprc > flag->prc && !flag->dash && flag->prc <= flag->nbrlen && nbr == 0)
			treat_flag(flag, flag->newprc, 0);
	}
	if (nbr < 0)
		ft_putchar_fd('-', 1);
	if (flag->prc > flag->nbrlen)
	{
		flag->zero = 1;
		if (flag->prc > flag->nbrlen && flag->dash)
			treat_flag(flag, flag->prc, flag->nbrlen);
	}
}

static int	treat_neg(int nbr)
{
		nbr *= -1;
		ft_putchar_fd('-', 1);
		return(nbr);
}

static void	treat_space(t_flags *flag)
{
	ft_putchar_fd(' ', 1);
	flag->flen++;
}

static void	treat_sign(t_flags *flag)
{
	ft_putchar_fd('+', 1);
	flag->flen++;
}

static void	print_number_di(int nbr, t_flags *flag, int number)
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

static void	print_di(int nbr, t_flags *flag)
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

static void	ft_putunbr_fd(unsigned int n, int fd)
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

static void	print_u(unsigned int nbr, t_flags *flag)
{
	flag->nbrlen = get_unbrlen(nbr);
	if (flag->dot)
		treat_dot_flag_upxX(nbr, flag);
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

static void	print_hexa (unsigned int i, t_flags *flag)
{
	if (i >= 16)
	{
		print_hexa(i / 16, flag);
		print_hexa(i % 16, flag);
	}
	else
		ft_putchar_fd(HEXALOW[i], 1);
}

static int	get_hexaplen(unsigned int i)
{
	int len;

	len = 0;
	if (i == 0)
		len = 1;
	if (i < 0)
	{
		i *= -1;
		len++;
	}
	while (i > 0)
	{
		i = i / 16;
		len ++;
	}
	return (len);
}

static void	print_hexap(unsigned long i)
{
	if (i >= 16)
	{
		print_hexap(i / 16);
		print_hexap(i % 16);
	}
	else
		ft_putchar_fd(HEXALOW[i], 1);
}

static int	get_hexaplonglen(unsigned long i)
{
	int len;

	len = 0;
	if (i == 0)
		len = 1;
	if (i < 0)
	{
		i *= -1;
		len++;
	}
	while (i > 0)
	{
		i = i / 16;
		len ++;
	}
	return (len);
}

static void	print_p(unsigned long nbr, t_flags *flag)
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

static void	print_x(unsigned int nbr, t_flags *flag)
{
	flag->nbrlen = get_hexaplen(nbr);
	if (flag->hash && nbr > 0)
	{
		ft_putstr_fd("0x", 1);
		flag->flen += 2;
	}
	if (flag->dot)
		treat_dot_flag_upxX(nbr, flag);
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

static void	print_hexaup(unsigned int i, t_flags *flag)
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

static void	treat_dot_flag_upxX(unsigned int nbr, t_flags *flag)
{
	if (flag->newprc > flag->prc)
	{
		flag->zero = 0;
		if(flag->newprc > flag->prc && !flag->dash && flag->prc > flag->nbrlen)
		treat_flag(flag, flag->newprc, flag->prc);
		if(flag->newprc > flag->prc && !flag->dash && flag->prc <= flag->nbrlen && nbr != 0)
			treat_flag(flag, flag->newprc, flag->nbrlen);
		if(flag->newprc > flag->prc && !flag->dash && flag->prc <= flag->nbrlen && nbr == 0)
			treat_flag(flag, flag->newprc, 0);
	}
	if (flag->prc > flag->nbrlen)
	{
		flag->zero = 1;
		if (flag->prc > flag->nbrlen && flag->dash)
			treat_flag(flag, flag->prc, flag->nbrlen);
	}
}

static void treat_dash_flag(unsigned int nbr, t_flags *flag)
{
	if (flag->dash && flag->newprc > flag->prc && flag->prc > flag->nbrlen)
		flag->zero = 0;
	if (flag->dash && flag->prc < flag->newprc && flag->prc <= flag->nbrlen && nbr != 0)
		treat_flag(flag, flag->newprc, flag->nbrlen);
	if (flag->dash && flag->prc < flag->newprc && flag->prc <= flag->nbrlen && nbr == 0)
		treat_flag(flag, flag->newprc, 0);
	if (flag->dash && flag->newprc > flag->prc && flag->prc > flag->nbrlen)
		treat_flag(flag, flag->newprc, flag->prc);
	if (flag->dash && !flag->dot)
		treat_flag(flag, flag->prc, flag->nbrlen);
}

static void	print_xup(unsigned int nbr, t_flags *flag)
{
	flag->nbrlen = get_hexaplen(nbr);
	if (flag->hash && nbr > 0)
	{
		ft_putstr_fd("0X", 1);
		flag->flen += 2;
	}
	if (flag->dot)
		treat_dot_flag_upxX(nbr, flag);
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

static int	print_char(t_flags *flag , const char *str, int i)
{
	if (flag->dash && flag->zero)
		flag->zero = 0;
	if (str[i] == 'c')
		print_c(va_arg(flag->args, int),flag);
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

int	ft_printf(const char *str, ...)
{
	int i;
	int len;
	t_flags *flags;

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
