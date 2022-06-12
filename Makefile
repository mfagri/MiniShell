# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/21 19:42:03 by aaitoual          #+#    #+#              #
#    Updated: 2022/06/12 12:06:47 by mfagri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc 
FLAGS = -Wall -Wextra -Werror 
LFLAGS	= -I/Users/$(USER)/.brew/opt/readline/include
AR = ar rcs
OBJECT_PATH = ./object_files/

FILE =  minishell.c ft_split.c ft_strncmp.c get_next_line_utils.c \
		get_next_line.c ft_strlen.c ft_strjoin.c utils_1.c \
		ft_strlcpy.c ft_isdigit.c ft_isalnum.c ft_itoa.c\
		handler.c utils_2.c quotations.c get_arg.c \
		vars.c separation.c ft_export.c \
		builtins.c builtins_utils.c ft_export_utils_1.c ft_export_utils_2.c\
		builtins_utils_2.c vars_utils.c get_command.c get_command_utils.c \
		check_pr.c ft_atoi.c ft_strchr.c  rederections.c\
		builtins_utils_3.c rederections_utils_2.c rederections_utils_1.c\
		exec.c builtins_utils_4.c rederections_utils_4.c exec_utils_1.c\
		utils_3.c utils_4.c check_pr_utils_1.c utils_5.c \


LIB = ./mandatory/minishell.h

OBJECTS = $(addprefix $(OBJECT_PATH), $(FILE:.c=.o))
all: object_files $(NAME) 

$(NAME): $(OBJECTS) $(LIB)
	$(CC) $(OBJECTS) $(FLAGS) $(LFLAGS) -o $@  -lreadline -L/Users/$(USER)/.brew/opt/readline/lib

$(OBJECT_PATH)%.o  : ./mandatory/%.c
	$(CC) $(LFLAGS) $(LFLAGS) -o $@  -c $^

$(OBJECT_PATH)%.o : ./mandatory/utils/%.c
	$(CC) $(LFLAGS) $(FLAGS) -o $@  -c $^

object_files :
	@mkdir object_files 

clean:
	rm -f $(OBJECTS) $(FILE1_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
re: fclean all
