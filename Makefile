# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmago <mmago@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/15 21:13:09 by mmago             #+#    #+#              #
#    Updated: 2022/06/13 20:48:00 by mmago            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

NAME_B = philo_bonus

CC = gcc
# -fsanitize=thread флаг для теста потока
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

FILES_B =	philo_two/src/main.c philo_two/src/utils.c philo_two/src/dop_fail.c\
			philo_two/src/init.c philo_two/src/action.c	\

FILES = philo_one/src/main.c philo_one/src/utils.c \
		philo_one/src/init.c philo_one/src/action.c \
					
OBJS = $(FILES:%.c=%.o)

OBJS_B = $(FILES_B:%.c=%.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(NAME_B): $(OBJS_B)
	$(CC) $(CFLAGS) $(OBJS_B) -o $(NAME_B)

all: $(NAME)

bonus: $(NAME_B)

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS_B)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME_B)

re: fclean all

.PHONY:all bonus clean fclean re
