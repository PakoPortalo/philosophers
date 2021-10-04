# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/03 10:21:55 by fportalo          #+#    #+#              #
#    Updated: 2021/09/30 16:39:15 by fportalo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

CC = gcc

FLAGS = -Wall -Wextra -Werror -g

SRC = philo.c handle_parse.c philo_utils_1.c philo_utils_2.c threads.c routines.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
		@$(CC) $(FLAGS) -c $(SRC)
		@$(CC) $(FLAGS) $(OBJ) -o $(NAME)

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
	norminette $(SRC)

.PHONY: all clean fclean re
