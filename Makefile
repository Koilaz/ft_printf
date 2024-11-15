  # **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmarck <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/21 20:46:04 by lmarck            #+#    #+#              #
#    Updated: 2024/11/04 20:53:48 by lmarck           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=\
	ft_printf.c \
	iput_pxc.c\
	iput_usd.c\

OBJS	=		${SRCS:.c=.o}

NAME	=		libftprintf.a
CC	=		cc
CFLAGS =	-Wall -Wextra -Werror -g3 -I.
RM =		rm -f

all: 		${NAME}

$(NAME):	$(OBJS)
			ar -rc $(NAME) $(OBJS)

clean:
			${RM} ${OBJS}
fclean: 	clean
			${RM} ${NAME}

re: 		fclean all

.PHONY:		bonus all clean fclean re
