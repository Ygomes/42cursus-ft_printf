/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygomes-d <ygomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 08:36:47 by ygomes-d          #+#    #+#             */
/*   Updated: 2021/10/31 09:58:58 by ygomes-d         ###   ########.fr       */
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
}	t_flags;

int	ft_printf(const char *str, ...);
t_flags *init_flags(t_flags  *flags);
t_flags *reinit_flags(t_flags  *flags);
int check_flags(const char *str, int i, t_flags *flags);
static unsigned int	get_unbrlen(unsigned int n);
static  int	get_nbrlen( int n);
void print_c(int chr, int count, t_flags *flag);
void print_s(char *str, int i, t_flags *flag, int newfl);
void print_di(int nbr,int i, t_flags *flag, int newfl);
void	ft_putunbr_fd(unsigned int n, int fd);
void print_u(unsigned int nbr, int i, t_flags *flag, int newfl);
void print_hexa (unsigned int i, t_flags *flag);
void print_hexap(unsigned long i);
static int get_hexaplonglen(unsigned long i);
void print_p(unsigned long i, t_flags *flag, int count);
static void	treat_dot_flag_upxX(unsigned int nbr, t_flags *flag, int count, int newfl);
static int	treat_dot_flag_di(int nbr, t_flags *flag, int count, int newfl);
static void treat_dash_flag(unsigned int nbr, t_flags *flag, int count, int newfl);
void print_x(unsigned int i, t_flags *flags, int count, int newfl);
void print_hexaup(unsigned int i, t_flags *flag);
void print_xup(unsigned int i, t_flags *flags, int count, int newfl);
int print_char(t_flags *flag , const char *str, int i, int fl, int newfl);
void treat_flag(t_flags *flag ,int count, int len);
char	*ft_pitoa(unsigned long n);
static int	strlcpydstlen(char *dst, const char *src, int size);

#endif
