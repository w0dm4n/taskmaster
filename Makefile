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

OBJS_PATH = ./objs/

INCLUDE_FOLDER = includes/

FILE_EXTENSION = cpp

SRCS_FILE = $(SRCS_PATH)/main.cpp

ALL_O_FILE = $(addprefix $(OBJS_PATH),$(notdir $(SRCS_FILE)))

ALL_O_FILE_SUITE = $(ALL_O_FILE:.$(FILE_EXTENSION)=.o)

HEADER_PATH = ./includes/

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@g++ $(FLAGS) -I $(INCLUDE_FOLDER) -o $(ALL_O_FILE_SUITE) -c $(SRCS_FILE) 
	@g++ -o $(NAME) $(ALL_O_FILE_SUITE) -I $(INCLUDE_FOLDER) -ltermcap

clean:
	@rm -rf $(ALL_O_FILE_SUITE)

fclean: clean
	@rm -rf $(NAME)

re:		fclean all

.PHONY: all clean fclean re
