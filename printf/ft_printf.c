/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygomes-d <ygomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 19:26:48 by ygomes-d          #+#    #+#             */
/*   Updated: 2021/10/22 11:42:54 by ygomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

t_flags *init_flags(t_flags  *flags)
{
	flags->wdt = 0;
	flags->prs = 0;
	flags->zero = 0;
	flags->dot = 0;
	flags->dash = 0;
	flags->sign = 0;
	flags->space = 0;
	return (flags);
}

int check_flags(const char *str, int i)
{
	t_flags *flags;
	if (str[i] == '0')
	{
		flags->zero = 1;
		i++;
	}
	if (str[i] == '.')
	{
		flags->prs = 1;
		i++;
	}
	if (str[i] == '-')
	{
		flags->dash= 1;
		i++;
	}
	if (str[i] == ' ')
	{
		flags->space= 1;
		i++;
	}
	if (ft_isdigit(str[i]))
	{
		flags->wdt = 1;
		i++;
	}
	return (i);
}

static unsigned int	get_len(unsigned int n)
{
	unsigned int	i;
	unsigned int	nbr;

	i = 0;
	nbr = n;
	while (nbr)
	{
		i++;
		nbr = nbr / 10;
	}
	return (i);
}

void print_c(int chr, t_flags *flags)
{
	ft_putchar_fd(chr, 0);
}

void print_s(char *str, t_flags *flags)
{
	ft_putstr_fd(str, 0);
}

void print_di(int nbr,int i, t_flags *flag)
{
	int len;
	int count;

	count = i;
	len = get_len(nbr);
	 if (flag->wdt)
	{
		while (count - len > 0)
		{
			ft_putnbr_fd(0, 0);
			count--;
		}
	}
	ft_putnbr_fd(nbr, 0);
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
	ft_putunbr_fd(i, 0);
}

void print_hexa (unsigned int i)
{
	if (i >= 16)
	{
		print_hexa(i / 16);
		print_hexa(i % 16);
	}
	else
	{
		ft_putchar_fd(HEXALOW[i], 0);
	}
}

void print_p(unsigned long i, t_flags *flags)
{
	print_hexa(i);
}

void print_x(unsigned int i, t_flags *flags)
{
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
		ft_putchar_fd(HEXAUP[i], 0);
	}
}

void print_xup(unsigned int i, t_flags *flags)
{
	print_hexaup(i);
}

int print_char(t_flags *flag , const char *str, int i)
{
	int fl;

	fl = str[i - 1] - 48;
	if (str[i] == 'c')
		print_c(va_arg(flag->args, int), flag);
	if (str[i] == 's')
		print_s(va_arg(flag->args, char *), flag);
	if (str[i] == 'd' || str[i] == 'i')
		print_di(va_arg(flag->args, int), fl, flag);
	if (str[i] == 'u')
		print_u(va_arg(flag->args, unsigned int), flag);
	if (str[i] == 'p')
		print_p(va_arg(flag->args, unsigned long), flag);
	if (str[i] == 'x')
		print_x(va_arg(flag->args, unsigned int), flag);
	if (str[i] == 'X')
		print_xup(va_arg(flag->args, unsigned int), flag);
	if (str[i] == '%')
		putchar_fd('%', 0);
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
		{
			i = check_flags(str, i + 1);
			print_char(flags ,str, i);
		}
		else
			ft_putchar_fd(str[i], 0);
	}
	va_end (flags->args);
	free (flags);
	return (len);
}

int main()
{
	int x = 50000;
	int *ptr = &x;
	char *Y = "Marreco";
	ft_printf("%% MINHA \n");
	printf("%% ORIGINAL \n");
}
