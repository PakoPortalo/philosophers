# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/03 10:21:55 by fportalo          #+#    #+#              #
#    Updated: 2021/10/08 12:47:05 by fportalo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

SRC = philo.c handle_parse.c philo_utils_1.c philo_utils_2.c threads.c routines.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $^ -o $@

clean:
		@rm -rf $(OBJ)

fclean: clean
		@rm -rf $(NAME)

re: fclean all

try:
	./philo 4 400 100 100

dead:
	./philo 4 100 50 100

normi:
	norminette $(SRC) philo.h

.PHONY: all clean fclean re
