/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygomes-d <ygomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 19:26:48 by ygomes-d          #+#    #+#             */
/*   Updated: 2021/10/26 10:18:27 by ygomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

t_flags *init_flags(t_flags  *flags)
{
	flags->wdt = 0;
	flags->zero = 0;
	flags->dot = 0;
	flags->dash = 0;
	flags->sign = 0;
	flags->space = 0;
	flags->hash = 0;
	return (flags);
}

int check_w(const char *str, int i)
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

int check_flags(const char *str, int i)
{
	t_flags *flags;
	int fl;
	char *check;
	int j;
	int newfl;

	fl = 0;
	j = 0;
	check = "udcsupxX%";
	newfl = 0;
	while (str[i] != check[j++])
	{
		if (str[i] == '.' && !flags->wdt)
		{
			flags->dot = 1;
			flags->zero = 1;
			i++;
		}
		if (ft_isdigit(str[i]))
		{
			if (!flags->wdt)
				fl = check_w(str, i);
			if (flags->zero && !flags->dot)
			{
				newfl = fl - check_w(str, i);
				fl = check_w(str, i);
			}
			flags->wdt = 1;
			i += get_nbrlen(fl);
		}
		if (str[i] == '+')
		{
			flags->sign = 1;
			i++;
		}
		if (str[i] == '-')
		{
			flags->dash= 1;
			i++;
		}
		if (str[i] == '0' && !flags->wdt)
		{
			flags->zero = 1;
			i++;
		}
		if (str[i] == '.')
		{
			if (flags->wdt && !ft_isdigit(str[i + 1]))
				flags->space= 1;
			else
				flags->zero = 1;
			i++;
		}
		if (str[i] == ' ')
		{
			flags->space= 1;
			i++;
		}
		if (str[i] == '#')
		{
			flags->hash = 1;
			i++;
		}
	}
	print_char(flags ,str, i, fl, newfl);
	return (i);
}

static unsigned int	get_nbrlen(unsigned int n)
{
	unsigned int	i;
	unsigned int	nbr;

	i = 0;
	nbr = n;
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

void print_c(int chr, t_flags *flags)
{
	ft_putchar_fd(chr, 1);
}

void print_s(char *str, int i, t_flags *flag, int newfl)
{
	int len;
	int count;

	count = i;
	len = ft_strlen(str);
	if (newfl != 0 || flag->dot)
		count = 0;
	if (flag->zero)
		flag->zero = 0;
	if (flag->wdt && !flag->dash)
		treat_dash(flag, count, len);
	ft_putstr_fd(str, 1);
	if (flag->dash && flag->wdt)
		treat_dash(flag, count, len);
}

void treat_dash(t_flags *flag ,int count, int len)
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
		}
}

void print_di(int nbr,int i, t_flags *flag, int newfl)
{
	int len;
	int count;

	count = i;
	len = get_nbrlen(nbr);
	if (newfl > i)
		treat_dash(flag, newfl, 0);
	if (flag->wdt && !flag->dash)
		treat_dash(flag, count, len);
	if (flag->sign)
		ft_putchar_fd('+', 1);
	ft_putnbr_fd(nbr, 1);
	if (flag->dash && flag->wdt)
		treat_dash(flag, count, len);
}

void	ft_putunbr_fd(unsigned int n, int fd)
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

void print_u(unsigned int i, t_flags *flags)
{
	ft_putunbr_fd(i, 1);
}

void print_hexa (unsigned int i)
{
	if (i >= 16)
	{
		print_hexa(i / 16);
		print_hexa(i % 16);
	}
	else
		ft_putchar_fd(HEXALOW[i], 1);
}

/* static int get_hexaplen(unsigned int i)
{
	int len;

	len = 0;
	if (i < 0);
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
} */

void print_hexap(unsigned int i)
{
	if (i >= 16)
	{
		print_hexap(i / 16);
		print_hexap(i % 16);
	}
	else
		ft_putchar_fd(HEXALOW[i], 1);
}

/* static char *make_hexap(unsigned int i)
{
	char *str;
	int j;

	j = get_hexaplen(i) + 1;
	str = malloc(sizeof(char) * j);
	str[j] = '\0';
	/while (i > 0)
	{
		if (i >= 16)
		{
			i = make_hexapp(i);
			printf("|%d|", i);
		}
		else
			str[--j] = HEXALOW[i];
	}
	printf("%s// %d//", str, j);
	return (str);
} */

void print_p(unsigned long i, t_flags *flags)
{
	print_hexap(i);
}

void print_x(unsigned int i, t_flags *flags)
{
	if (flags->hash)
		ft_putstr_fd("0x", 1);
	print_hexa(i);
}

void print_hexaup(unsigned int i)
{
	if (i >= 16)
	{
		print_hexaup(i / 16);
		print_hexaup(i % 16);
	}
	else
	{
		ft_putchar_fd(HEXAUP[i], 1);
	}
}

void print_xup(unsigned int i, t_flags *flags)
{
	if (flags->hash)
		ft_putstr_fd("0x", 1);
	print_hexaup(i);
}

int print_char(t_flags *flag , const char *str, int i, int fl, int newfl)
{
	if (str[i] == 'c')
		print_c(va_arg(flag->args, int), flag);
	if (str[i] == 's')
		print_s(va_arg(flag->args, char *), fl, flag, newfl);
	if (str[i] == 'd' || str[i] == 'i')
		print_di(va_arg(flag->args, int), fl, flag, newfl);
	if (str[i] == 'u')
		print_u(va_arg(flag->args, unsigned int), flag);
	if (str[i] == 'p')
		print_p(va_arg(flag->args, unsigned long), flag);
	if (str[i] == 'x')
		print_x(va_arg(flag->args, unsigned int), flag);
	if (str[i] == 'X')
		print_xup(va_arg(flag->args, unsigned int), flag);
	if (str[i] == '%')
		ft_putchar_fd('%', 1);
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
			i = check_flags(str, i + 1);
		else
			ft_putchar_fd(str[i], 1);
	}
	va_end (flags->args);
	free (flags);
	return (len);
}

int main()
{
	int x = 5;
	int *ptr = &x;
	char *Y = "Marreco";
	ft_printf("%.12d MINHA \n", x);
	printf("%.12d ORIGINAL \n", x);
}
