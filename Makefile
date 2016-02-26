# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/17 08:34:59 by frmarinh          #+#    #+#              #
#    Updated: 2016/02/18 01:35:59 by frmarinh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = taskmaster

SRCS_PATH = ./srcs

INCLUDE_FOLDER = includes/

FILE_EXTENSION = cpp

SRCS_FILE = $(SRCS_PATH)/main.cpp $(SRCS_PATH)/config.cpp $(SRCS_PATH)/handle_config.cpp $(SRCS_PATH)/handle_taskmaster_var.cpp

ALL_O_FILE = $(notdir $(SRCS_FILE))

ALL_O_FILE_SUITE = $(ALL_O_FILE:.$(FILE_EXTENSION)=.o)

HEADER_PATH = ./includes/

FLAGS = -ggdb

all: $(NAME)

$(NAME):
	@g++ $(FLAGS) -I $(INCLUDE_FOLDER) -c $(SRCS_FILE)
	@g++ -o $(NAME) $(ALL_O_FILE_SUITE) -I $(INCLUDE_FOLDER) -ltermcap

clean:
	@rm -rf $(ALL_O_FILE_SUITE)

fclean: clean
	@rm -rf $(NAME)

re:		fclean all

.PHONY: all clean fclean re
