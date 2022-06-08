# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/21 19:42:03 by aaitoual          #+#    #+#              #
#    Updated: 2022/06/08 09:52:56 by mfagri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc 
FLAGS = -Wall -Wextra -Werror 
LFLAGS	= -I/Users/$(USER)/.brew/opt/readline/include
AR = ar rcs
OBJ = ./mandatory/obj

FILE =  ./mandatory/minishell.c ./mandatory/utils/ft_split.c ./mandatory/utils/ft_strncmp.c ./mandatory/utils/get_next_line_utils.c \
		./mandatory/utils/get_next_line.c ./mandatory/utils/ft_strlen.c ./mandatory/utils/ft_strjoin.c ./mandatory/utils/utils_1.c \
		./mandatory/utils/ft_strlcpy.c ./mandatory/utils/ft_isdigit.c ./mandatory/utils/ft_isalnum.c ./mandatory/utils/ft_itoa.c\
		./mandatory/utils/handler.c ./mandatory/utils/utils_2.c ./mandatory/utils/quotations.c ./mandatory/utils/get_arg.c \
		./mandatory/utils/vars.c ./mandatory/utils/separation.c ./mandatory/utils/ft_export.c \
		./mandatory/utils/builtins.c ./mandatory/utils/builtins_utils.c ./mandatory/utils/ft_export_utils_1.c ./mandatory/utils/ft_export_utils_2.c\
		./mandatory/utils/builtins_utils_2.c ./mandatory/utils/vars_utils.c ./mandatory/utils/get_command.c ./mandatory/utils/get_command_utils.c \
		./mandatory/utils/check_pr.c ./mandatory/utils/ft_atoi.c ./mandatory/utils/ft_strchr.c  ./mandatory/utils/rederections.c\
		./mandatory/utils/builtins_utils_3.c ./mandatory/utils/rederections_utils_2.c ./mandatory/utils/rederections_utils_1.c\
		./mandatory/utils/exec.c\

FILE1 = $(FILE:.c=.o)

LIB = ./mandatory/minishell.h 

all: $(NAME)

$(NAME): $(FILE1) $(LIB) 
	$(CC) $(FILE1) $(FLAGS) -o $@  -lreadline -L/Users/$(USER)/.brew/opt/readline/lib

%.o : %.c 
	$(CC) $(LFLAGS) -I $(LFLAGS) -o $@  -c $^

clean:
	rm -f $(FILE1) $(FILE1_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
re: fclean all