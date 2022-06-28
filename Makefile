# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/16 15:00:23 by alefranc          #+#    #+#              #
#    Updated: 2022/06/28 03:52:50 by alefranc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------------------------------------------------------------------------#
#                                                                              #
#                               DECLARATIONS                                   #
#                                                                              #
#------------------------------------------------------------------------------#

#------------------------------------#
#             COMPILATION            #
#------------------------------------#

NAME = philo

CC = clang
CFLAG = -Wall -Wextra -Werror #-O2
PROJINC_FLAG = -I include

#------------------------------------#
#               SOURCES              #
#------------------------------------#

SRCDIR = src/
SRCFILES =	main.c \
			init_sim.c \
			monitor.c \
			philo_action.c \
			print_states.c \
			start_sim.c \
			utils.c \
			utils2.c


SRC = $(addprefix $(SRCDIR), $(SRCFILES))

#------------------------------------#
#               OBJECTS              #
#------------------------------------#

OBJDIR = obj/
OBJ = $(addprefix $(OBJDIR), $(SRCFILES:.c=.o))

#------------------------------------#
#               HEADER               #
#------------------------------------#

HEADER = include/philo.h

#------------------------------------#
#              SUMMARY               #
#------------------------------------#

LIB_ARCHIVE =
INC_FLAG = $(PROJINC_FLAG)
LIB_PATH =
LIB_FLAG = -pthread

#------------------------------------------------------------------------------#
#                                                                              #
#                                   RULES                                      #
#                                                                              #
#------------------------------------------------------------------------------#

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAG) $(OBJ) -o $(NAME) $(LIB_ARCHIVE) $(INC_FLAG) $(LIB_PATH) $(LIB_FLAG)

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADER)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAG) -c $< -o $@ $(INC_FLAG)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
