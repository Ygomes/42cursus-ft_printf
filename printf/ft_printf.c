/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygomes-d <ygomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 19:26:48 by ygomes-d          #+#    #+#             */
/*   Updated: 2021/10/30 12:32:33 by ygomes-d         ###   ########.fr       */
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

int check_udicpxX(const char *str, int i)
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

int check_flags(const char *str, int i, t_flags *flags)
{
	int fl;
	char *check;
	int j;
	int newfl;

	fl = 0;
	j = 0;
	check = "udicspxX%";
	newfl = 0;
	while (str[i] != check[j++])
	{
		while (str[i] == '0')
		{
			flags->zero = 1;
			i++;
		}
		if (ft_isdigit(str[i]))
		{
			fl = check_w(str, i);
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
			flags->dot = 1;
			i++;
			while(str[i] == '0')
			{
				flags->zero = 0;
				i++;
			}
			if (check_udicpxX(str, i))
				flags->zero = 0;
			newfl = fl;
			fl = check_w(str, i);

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

void print_c(int chr, int count, t_flags *flag)
{
	if (flag->zero)
		flag->zero = 0;
	if (flag->wdt && !flag->dash)
		treat_flag(flag, count, 1);
	ft_putchar_fd(chr, 1);
	if (flag->dash && flag->wdt)
		treat_flag(flag, count, 1);
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

void print_s(char *str, int count, t_flags *flag, int newfl)
{
	int len;
	char *newstr;
	int  newlen;

	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	newstr = malloc(sizeof(char) * (len + 1));
	if (!newstr)
		free(newstr);
	newlen = len;
	if (flag->zero)
		flag->zero = 0;
	if (flag->wdt && !flag->dash && !flag->dot)
		treat_flag(flag, count, newlen);
	if (flag->dot)
	{
		newlen = strlcpydstlen(newstr, str, count + 1);
		ft_putstr_fd(newstr, 1);
		if (flag->dash)
			treat_flag(flag, newfl, newlen);
	}
	else
		ft_putstr_fd(str, 1);
	if (flag->dash && flag->wdt && !flag->dot)
		treat_flag(flag, count, newlen);
	flag->flen += newlen;
	free(newstr);
	reinit_flags(flag);
}

void treat_flag(t_flags *flag ,int count, int len)
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

void	ft_putlongnbr_fd(long int n, int fd)
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

void print_di(int nbr,int count, t_flags *flag, int newfl)
{
	int len;
	int number;

	number = nbr;
	len = get_nbrlen(nbr);
	if (nbr < -2147483647)
		len = 11;
	if (flag->dot)
	{
		if (nbr < 0)
			count++;
		if (newfl > count)
		{
			flag->zero = 0;
			if(newfl > count && !flag->dash && count > len)
				treat_flag(flag, newfl, count);
			if(newfl > count && !flag->dash && count <= len && nbr != 0)
				treat_flag(flag, newfl, len);
			if(newfl > count && !flag->dash && count <= len && nbr == 0)
				treat_flag(flag, newfl, 0);
		}
		if (nbr < 0)
		{
			number *= -1;
			ft_putchar_fd('-', 1);
		}
		if (count > len)
		{
			flag->zero = 1;
			if (count > len && flag->dash)
				treat_flag(flag, count, len);
		}
	}
	if (nbr < 0 && !flag->dot && flag->zero)
	{
		number *= -1;
		ft_putchar_fd('-', 1);
	}
	if (!flag->dash && flag->wdt)
		treat_flag(flag, count, len);
	if (flag->space && !flag->wdt && nbr >= 0)
	{
		ft_putchar_fd(' ', 1);
		flag->flen++;
	}
	if (nbr < 0 && !flag->dot && !flag->zero)
	{
		number *= -1;
		ft_putchar_fd('-', 1);
	}
	if (flag->sign && nbr >= 0)
	{
		ft_putchar_fd('+', 1);
		flag->flen++;
	}
	if (flag->dot && nbr == 0 && count == 0)
		treat_flag(flag, 0, 0);
	else if (nbr < -2147483647)
	{
		put_long_nbr(nbr);
		flag->flen += len;
	}
	else
	{
		ft_putnbr_fd(number, 1);
		flag->flen += len;
	}
	if (flag->dash && newfl > count && count > len)
		flag->zero = 0;
	if (flag->dash && count < newfl && count <= len && nbr != 0)
		treat_flag(flag, newfl, len);
	if (flag->dash && count < newfl && count <= len && nbr == 0)
		treat_flag(flag, newfl, 0);
	if (flag->dash && newfl > count && count > len)
		treat_flag(flag, newfl, count);
	if (flag->dash && !flag->dot)
		treat_flag(flag, count, len);
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

void print_u(unsigned int nbr, int count, t_flags *flag, int newfl)
{
	int len;

	len = get_unbrlen(nbr);
	if (flag->dot)
	{
		if (newfl > count)
		{
			flag->zero = 0;
			if(newfl > count && !flag->dash && count > len)
				treat_flag(flag, newfl, count);
			if(newfl > count && !flag->dash && count <= len && nbr != 0)
				treat_flag(flag, newfl, len);
			if(newfl > count && !flag->dash && count <= len && nbr == 0)
				treat_flag(flag, newfl, 0);
		}
		if (count > len)
		{
			flag->zero = 1;
			if (count > len && flag->dash)
				treat_flag(flag, count, len);
		}
	}
	if (!flag->dash && flag->wdt)
		treat_flag(flag, count, len);
	if (flag->dot && nbr == 0 && count == 0)
		treat_flag(flag, 0, 0);
	else
	{
		ft_putunbr_fd(nbr, 1);
		flag->flen += len;
	}
	if (flag->dash && newfl > count && count > len)
		flag->zero = 0;
	if (flag->dash && count < newfl && count <= len && nbr != 0)
		treat_flag(flag, newfl, len);
	if (flag->dash && count < newfl && count <= len && nbr == 0)
		treat_flag(flag, newfl, 0);
	if (flag->dash && newfl > count && count > len)
		treat_flag(flag, newfl, count);
	if (flag->dash && !flag->dot)
		treat_flag(flag, count, len);
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

void print_hexap(unsigned long i)
{
	if (i >= 16)
	{
		print_hexap(i / 16);
		print_hexap(i % 16);
	}
	else
		ft_putchar_fd(HEXALOW[i], 1);
}

static int get_hexaplonglen(unsigned long i)
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

void print_p(unsigned long i, t_flags *flag, int count)
{
	int len;

	len = get_hexaplonglen(i);
	len += 2;
	if (!flag->dash && flag->wdt)
		treat_flag(flag, count, len);
	ft_putstr_fd("0x", 1);
	print_hexap(i);
	flag->flen += len;
	if (flag->dash && flag->wdt)
		treat_flag(flag, count, len);
	reinit_flags(flag);
}

void print_x(unsigned int i, t_flags *flag, int count, int newfl)
{
	int len;

	len = get_hexaplen(i);
	if (flag->hash && i > 0)
	{
		ft_putstr_fd("0x", 1);
		flag->flen += 2;
	}
	if (flag->dot)
	{
		if (newfl > count)
		{
			flag->zero = 0;
			if(newfl > count && !flag->dash && count > len)
				treat_flag(flag, newfl, count);
			if(newfl > count && !flag->dash && count <= len && i != 0)
				treat_flag(flag, newfl, len);
			if(newfl > count && !flag->dash && count <= len && i == 0)
				treat_flag(flag, newfl, 0);
		}
		if (count > len)
		{
			flag->zero = 1;
			if (count > len && flag->dash)
				treat_flag(flag, count, len);
		}
	}
	if (!flag->dash && flag->wdt)
		treat_flag(flag, count, len);
	if (flag->dot && i == 0 && count == 0)
		treat_flag(flag, 0, 0);
	else
	{
		print_hexa(i, flag);
		flag->flen += len;
	}
	if (flag->dash && newfl > count && count > len)
		flag->zero = 0;
	if (flag->dash && count < newfl && count <= len && i != 0)
		treat_flag(flag, newfl, len);
	if (flag->dash && count < newfl && count <= len && i == 0)
		treat_flag(flag, newfl, 0);
	if (flag->dash && newfl > count && count > len)
		treat_flag(flag, newfl, count);
	if (flag->dash && !flag->dot)
		treat_flag(flag, count, len);
	reinit_flags(flag);
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

void print_xup(unsigned int i, t_flags *flag, int count, int newfl)
{
	int len;

	len = get_hexaplen(i);
	if (flag->hash && i > 0)
	{
		ft_putstr_fd("0X", 1);
		flag->flen += 2;
	}
	if (flag->dot)
	{
		if (newfl > count)
		{
			flag->zero = 0;
			if(newfl > count && !flag->dash && count > len)
				treat_flag(flag, newfl, count);
			if(newfl > count && !flag->dash && count <= len && i != 0)
				treat_flag(flag, newfl, len);
			if(newfl > count && !flag->dash && count <= len && i == 0)
				treat_flag(flag, newfl, 0);
		}
		if (count > len)
		{
			flag->zero = 1;
			if (count > len && flag->dash)
				treat_flag(flag, count, len);
		}
	}
	if (!flag->dash && flag->wdt)
		treat_flag(flag, count, len);
	if (flag->dot && i == 0 && count == 0)
		treat_flag(flag, 0, 0);
	else
	{
		print_hexaup(i, flag);
		flag->flen += len;
	}
	if (flag->dash && newfl > count && count > len)
		flag->zero = 0;
	if (flag->dash && count < newfl && count <= len && i != 0)
		treat_flag(flag, newfl, len);
	if (flag->dash && count < newfl && count <= len && i == 0)
		treat_flag(flag, newfl, 0);
	if (flag->dash && newfl > count && count > len)
		treat_flag(flag, newfl, count);
	if (flag->dash && !flag->dot)
		treat_flag(flag, count, len);
	reinit_flags(flag);
}

int print_char(t_flags *flag , const char *str, int i, int fl, int newfl)
{
	if (flag->dash && flag->zero)
		flag->zero = 0;
	if (str[i] == 'c')
		print_c(va_arg(flag->args, int), fl, flag);
	if (str[i] == 's')
		print_s(va_arg(flag->args, char *), fl, flag, newfl);
	if (str[i] == 'd' || str[i] == 'i')
		print_di(va_arg(flag->args, int), fl, flag, newfl);
	if (str[i] == 'u')
		print_u(va_arg(flag->args, unsigned int), fl, flag, newfl);
	if (str[i] == 'p')
		print_p(va_arg(flag->args, unsigned long), flag, fl);
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

/* int main()
{
	int x = 0;
	int *ptr = &x;
	char *Y = "Marreco";
	char *null_str = NULL;
	ft_printf("%-1p %-2p MINHA\n", ptr, ptr);
	printf("%-1p %-2p ORIGINAL\n", ptr, ptr);
} */
