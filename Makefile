# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaitoual <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/21 19:42:03 by aaitoual          #+#    #+#              #
#    Updated: 2022/03/21 19:42:07 by aaitoual         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror
AR = ar rcs
OBJ = ./mandatory/obj

FILE =  ./mandatory/minishell.c ./mandatory/utils/ft_split.c ./mandatory/utils/ft_strncmp.c ./mandatory/utils/get_next_line_utils.c \
		./mandatory/utils/get_next_line.c ./mandatory/utils/ft_strlen.c ./mandatory/utils/ft_strjoin.c ./mandatory/utils/utils_1.c \
		./mandatory/utils/ft_strlcpy.c ./mandatory/utils/ft_isdigit.c ./mandatory/utils/ft_isalnum.c ./mandatory/utils/ft_itoa.c\

FILE1 = $(FILE:.c=.o)

LIB = ./mandatory/minishell.h \

all: $(NAME)

$(NAME): $(FILE1) $(LIB)
	@$(CC) $(FILE1) -o $@ -lreadline

%.o : %.c
	@$(CC) -o $@  -c $^

clean:
	@rm -f $(FILE1) $(FILE1_BONUS)

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
re: fclean all
