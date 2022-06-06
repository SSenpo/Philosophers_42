# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmago <mmago@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/15 21:13:09 by mmago             #+#    #+#              #
#    Updated: 2022/05/21 15:24:58 by mmago            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

# NAME_B = philo_bonus

CC = gcc
# gcc -fsanitize=thread флаг для теста потока
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

FILES = philo_one/src/main.c philo_one/src/utils.c \
		philo_one/src/init.c philo_one/src/action.c \
					
OBJS = $(FILES:%.c=%.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:all clean fclean re
