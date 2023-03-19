# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bammar <bammar@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/31 21:59:12 by bammar            #+#    #+#              #
#    Updated: 2023/03/19 15:43:45 by bammar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo_bonus

FILES	=	src/philo.c \
			src/ft_atol.c \
			src/ft_str_utils.c \
			src/parse_args.c \
			src/ft_strtrim.c \
			src/philo_init.c \
			src/philo_time.c \
			src/simulation.c \
			src/life.c \
			src/eat.c \
			src/psleep.c \
			src/msg.c \
			src/philo_destroy.c

CC		=	cc

CFLAGS	=	-Wall -Werror -Wextra  -I ./include -g

LINKS	=	-pthread

OBJS	=	$(FILES:.c=.o)

RM		=	/bin/rm

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT) $(LINKS) -o $(NAME)

clean:
	$(RM) -f $(OBJS)

fclean:	clean
	$(RM) -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
