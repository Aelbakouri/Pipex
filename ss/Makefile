# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-bako <ael-bako@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/02 11:34:05 by ael-bako          #+#    #+#              #
#    Updated: 2022/12/02 11:34:06 by ael-bako         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = pipex

CC = gcc -g3
CFLAGS = -Wall -Wextra -Werror


INC = ./inc/pipex.h \

SRC = \
	./src/main.c \
	./src/pipex.c \
	./src/pipex_utils.c \
	./src/string_utils.c \
	./src/ft_splitpath.c \
	./src/free.c \

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
