# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 15:52:20 by kczichow          #+#    #+#              #
#    Updated: 2023/01/24 16:14:12 by kczichow         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME 		= philo
#OS 			= $(shell uname)
 
# path to directories
SRCS_D		= srcs
OBJS_D		= obj
INC_D		= includes

# color codes for command line messages

BOLD	= \033[1m
BLACK	= \033[30;1m
RED		= \033[31;1m
GREEN	= \033[32;1m
YELLOW	= \033[33;1m
BLUE	= \033[34;1m
MAGENTA	= \033[35;1m
CYAN	= \033[36;1m
WHITE	= \033[37;1m
RESET	= \033[0m

# source and objects files

SRCS_F		=	philosophers.c \
				parse_and_init.c \
				manage_memory.c \
				manage_time.c \
				philo_actions.c \
				philo_print.c \
				check_exit.c
			  
SRCS_O		= $(addprefix $(OBJS_D)/, $(SRCS_F:%.c=%.o))

# compilation rules and flags
CC			= gcc -pthread -g
# CFLAGS		= -Wall -Wextra -Werror

#-fsanitize=address
ifdef DEBUGG
	CFLAGS +=  -g
else
	CFLAGS	+=  -D NDEBUG
endif

# -I option searches directories for #include directives
#INC_F		= -Iincludes

all:		$(NAME)

#dynamic rule to make sure Makefile does not relink

$(NAME):  $(OBJS_D) $(SRCS_O)
	 	$(CC) -o $(NAME) $(SRCS_O)
		  	
#compiles c files to o files, is called by $(SRCS_O)
$(OBJS_D)/%.o: $(SRCS_D)/%.c
			@echo "$(CYAN)compiling: $(RESET) $<"
			@$(CC) $(CFLAGS) -I $(INC_D) -c $< -o $@

$(OBJS_D):
	mkdir $@

clean:
	rm -rf $(OBJS_D)

fclean: clean
	rm -f $(NAME) 

re: fclean all

.PHONY: all clean fclean re