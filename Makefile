# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygomes-d <ygomes-d@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/26 11:24:12 by ygomes-d          #+#    #+#              #
#    Updated: 2021/11/01 12:20:01 by ygomes-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT 	= ./libft/libft.a

NAME =	libftprintf.a

CC =	clang

CFLAGS =	-Wall -Werror -Wextra -g

SRCS =	ft_printf.c \
		treat_flag_dotndash.c \
		get_length.c \
		check_case_conversion.c \
		make_cs.c \
		make_di.c \
		check_flags.c \
		treat_flags.c \
		make_up.c \
		make_xx.c \


OBJS =	$(SRCS:.c=.o)

RM =	rm -f

.c.o:
		$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
			$(MAKE) -C ./libft
			cp libft/libft.a $(NAME)
			ar rc $(NAME) $(OBJS)

all:	$(NAME)

bonus: all

clean:
		$(MAKE) clean -C ./libft
		$(RM) $(OBJS)

fclean:	clean
		$(MAKE) fclean -C ./libft
		$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re bonus
