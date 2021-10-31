/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygomes-d <ygomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 08:36:47 by ygomes-d          #+#    #+#             */
/*   Updated: 2021/10/31 11:43:57 by ygomes-d         ###   ########.fr       */
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
	int zero;
	int dot;
	int dash;
	int sign;
	int space;
	int hash;
	int flen;
	int nbrlen;
	int prc;
	int newprc;
}	t_flags;

t_flags	*init_flags(t_flags  *flags);
t_flags	*reinit_flags(t_flags  *flags);
static int	check_w(const char *str, int i);
static int	check_udicpxX(const char *str, int i);
static int	check_case(char c, t_flags *flag);
static int	check_dotwdt(const char *str, int i, t_flags *flag);
static int	check_flags(const char *str, int i, t_flags *flags);
static int	get_nbrlen( int n);
static unsigned int	get_unbrlen(unsigned int n);
static void	print_c(int chr, t_flags *flag);
static int	strlcpydstlen(char *dst, const char *src, int size);
static void	print_s(char *str, t_flags *flag);
static void	treat_flag(t_flags *flag ,int count, int len);
static void	ft_putlongnbr_fd(long int n, int fd);
static void	put_long_nbr(int n);
static void	treat_dot_flag_di(int nbr, t_flags *flag);
static int	treat_neg(int nbr);
static void	treat_space(t_flags *flag);
static void	treat_sign(t_flags *flag);
static void	print_number_di(int nbr, t_flags *flag, int number);
static void	print_di(int nbr, t_flags *flag);
static void	ft_putunbr_fd(unsigned int n, int fd);
static void	print_u(unsigned int nbr, t_flags *flag);
static void	print_hexa (unsigned int i, t_flags *flag);
static int	get_hexaplen(unsigned int i);
static void	print_hexap(unsigned long i);
static int	get_hexaplonglen(unsigned long i);
static void	print_p(unsigned long i, t_flags *flag);
static void	print_x(unsigned int nbr, t_flags *flag);
static void	print_hexaup(unsigned int i, t_flags *flag);
static void	treat_dot_flag_upxX(unsigned int nbr, t_flags *flag);
static void	treat_dash_flag(unsigned int nbr, t_flags *flag);
static void	print_xup(unsigned int i, t_flags *flags);
static int	print_char(t_flags *flag , const char *str, int i);
int	ft_printf(const char *str, ...);

#endif
