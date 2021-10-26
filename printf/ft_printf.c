/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygomes-d <ygomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 19:26:48 by ygomes-d          #+#    #+#             */
/*   Updated: 2021/10/26 20:06:13 by ygomes-d         ###   ########.fr       */
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
	flags->flen= 0;
	return (flags);
}

t_flags *reinit_flags(t_flags  *flags)
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

int check_flags(const char *str, int i, t_flags *flags)
{
	int fl;
	char *check;
	int j;
	int newfl;

	fl = 0;
	j = 0;
	check = "udicsupxX%";
	newfl = 0;
	while (str[i] != check[j++])
	{
		if (str[i] == '.' && !flags->wdt)
		{
			flags->dot = 1;
			flags->zero = 1;
			i++;
		}
		while (str[i] == '0' && !flags->wdt)
		{
			flags->zero = 1;
			i++;
		}
		if (ft_isdigit(str[i]))
		{
			if (!flags->wdt)
				fl = check_w(str, i);
			else if (flags->zero && !flags->dot)
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
		if (str[i] == '.')
		{
			if (flags->wdt && !ft_isdigit(str[i + 1]))
				flags->space= 1;
			else
				flags->zero = 2;
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

void print_c(int chr, int count, t_flags *flag, int newfl)
{

	if (newfl != 0 || flag->dot)
		count = 0;
	if (flag->zero)
		flag->zero = 0;
	if (flag->wdt && !flag->dash)
		treat_dash(flag, count, 1);
	ft_putchar_fd(chr, 1);
	if (flag->dash && flag->wdt)
		treat_dash(flag, count, 1);
	if (newfl > 1)
		flag->flen += newfl;
	else
		flag->flen++;
	reinit_flags(flag);
}

void print_s(char *str, int count, t_flags *flag, int newfl)
{
	int len;

	if (!str)
		str = "(null)";
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
	if (newfl > len)
		flag->flen += newfl;
	else
		flag->flen += len;
	reinit_flags(flag);
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
	int number;

	count = i;
	number = nbr;
	if (nbr < 0)
		if(flag->dash && !flag->sign)
			count--;
	len = get_nbrlen(number);
	if (nbr < 0 && flag->zero)
		{
			ft_putchar_fd('-', 1);
			newfl--;
			number *= -1;
		}
	if (newfl > i)
		treat_dash(flag, newfl, 0);
	if (flag->wdt && !flag->dash)
		treat_dash(flag, count, len);
	if (flag->space && !flag->wdt && nbr >= 0)
	{
		ft_putchar_fd(' ', 1);
		flag->flen++;
	}
	if (flag->sign && nbr >= 0)
	{
		ft_putchar_fd('+', 1);
		flag->flen++;
	}
	ft_putnbr_fd(number, 1);
	if (flag->dash && flag->wdt)
		treat_dash(flag, count, len);
	if (count > len)
		flag->flen += count;
	else
		flag->flen += len;
	reinit_flags(flag);
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

void print_u(unsigned int nbr, int i, t_flags *flag, int newfl)
{
	int len;
	int count;

	count = i;
	len = get_unbrlen(nbr);
	if (newfl > i)
		treat_dash(flag, newfl, 0);
	if (flag->wdt && !flag->dash)
		treat_dash(flag, count, len);
	if (flag->sign)
		flag->sign = 0;
	ft_putunbr_fd(nbr, 1);
	if (flag->dash && flag->wdt)
		treat_dash(flag, count, len);
	if (count > len)
		flag->flen += count;
	else
		flag->flen += len;
	reinit_flags(flag);
}

void print_hexa (unsigned int i, t_flags *flag)
{
	if (i >= 16)
	{
		print_hexa(i / 16, flag);
		print_hexa(i % 16, flag);
	}
	else
		ft_putchar_fd(HEXALOW[i], 1);
}

 static int get_hexaplen(unsigned int i)
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

void print_p(unsigned long i, t_flags *flag)
{
	flag->wdt = 1;
	print_hexap(i);
}

void print_x(unsigned int i, t_flags *flags, int count, int newfl)
{
	int len;

	len = get_hexaplen(i);
	/* printf("(|%d|-|%d| |%d|)", newfl, count, len); */
	if (flags->hash && i > 0)
	{
		ft_putstr_fd("0x", 1);
		flags->flen += 2;
	}
	if ((flags->zero == 2 && newfl > len) || newfl > 0)
	{
		flags->zero = 0;
		if (count > len)
		{
			treat_dash(flags, newfl, 0);
			flags->zero = 1;
			flags->flen += newfl;
		}
		else
			treat_dash(flags, newfl + count, len);
	}
	if (flags->wdt && !flags->dash)
		treat_dash(flags, count, len);
	print_hexa(i, flags);
	if (flags->dash && flags->wdt)
		treat_dash(flags, count, len);
 	if (count > len)
		flags->flen += count;
	else if (newfl > len)
		flags->flen += newfl + count;
	else
		flags->flen += len;
	reinit_flags(flags);
}

void print_hexaup(unsigned int i, t_flags *flag)
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

void print_xup(unsigned int i, t_flags *flags, int count, int newfl)
{
	int len;

	len = get_hexaplen(i);
	if (flags->hash && i > 0)
	{
		ft_putstr_fd("0X", 1);
		flags->flen += 2;
	}
	if ((flags->zero == 2 && newfl > len) || newfl > 0)
	{
		flags->zero = 0;
		if (count > len)
		{
			treat_dash(flags, newfl, 0);
			flags->zero = 1;
			flags->flen += newfl;
		}
		else
			treat_dash(flags, newfl + count, len);
	}
	if (flags->wdt && !flags->dash)
		treat_dash(flags, count, len);
	print_hexaup(i, flags);
	if (flags->dash && flags->wdt)
		treat_dash(flags, count, len);
 	if (count > len)
		flags->flen += count;
	else if (newfl > len)
		flags->flen += newfl + count;
	else
		flags->flen += len;
	reinit_flags(flags);
}

int print_char(t_flags *flag , const char *str, int i, int fl, int newfl)
{
	if (str[i] == 'c')
		print_c(va_arg(flag->args, int), fl, flag, newfl);
	if (str[i] == 's')
		print_s(va_arg(flag->args, char *), fl, flag, newfl);
	if (str[i] == 'd' || str[i] == 'i')
		print_di(va_arg(flag->args, int), fl, flag, newfl);
	if (str[i] == 'u')
		print_u(va_arg(flag->args, unsigned int), fl, flag, newfl);
	if (str[i] == 'p')
		print_p(va_arg(flag->args, unsigned long), flag);
	if (str[i] == 'x')
		print_x(va_arg(flag->args, unsigned int), flag, fl, newfl);
	if (str[i] == 'X')
		print_xup(va_arg(flag->args, unsigned int), flag, fl, newfl);
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

/*  int main()
{
	int x = -50;
	int *ptr = &x;
	char *Y = "Marreco";
	char *null_str = NULL;
	ft_printf("%014Xc%020Xs%02.5XX%0.Xi \n", -1, 3, 30, -1);
	printf("%14Xc%20Xs%02.5XX%0.Xi \n", -1, 3, 30, -1);
} */
