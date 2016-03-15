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

SRCS_FILE = $(SRCS_PATH)/main.cpp \
			$(SRCS_PATH)/config.cpp \
			$(SRCS_PATH)/handle_config.cpp \
			$(SRCS_PATH)/handle_taskmaster_var.cpp \
			$(SRCS_PATH)/ft_libft.cpp \
			$(SRCS_PATH)/print_error.cpp \
			$(SRCS_PATH)/get_new_program.cpp \
			$(SRCS_PATH)/get_program_args.cpp \
			$(SRCS_PATH)/check_all_program.cpp \
			$(SRCS_PATH)/handle_cmd.cpp \
			$(SRCS_PATH)/check_cmd.cpp \
			$(SRCS_PATH)/get_help_cmd.cpp \
			$(SRCS_PATH)/get_process_status.cpp \
			$(SRCS_PATH)/reload.cpp \
			$(SRCS_PATH)/start_program.cpp \
			$(SRCS_PATH)/handle_program.cpp \
			$(SRCS_PATH)/logs.cpp \
			$(SRCS_PATH)/utils.cpp \
			$(SRCS_PATH)/env.cpp \
			$(SRCS_PATH)/stop_program.cpp \
			$(SRCS_PATH)/restart_program.cpp \
			$(SRCS_PATH)/edit.cpp \
			$(SRCS_PATH)/handle_tabulation.cpp \
			$(SRCS_PATH)/read_user_entry.cpp

ALL_O_FILE = $(notdir $(SRCS_FILE))

ALL_O_FILE_SUITE = $(ALL_O_FILE:.$(FILE_EXTENSION)=.o)

HEADER_PATH = ./includes/

FLAGS =

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
