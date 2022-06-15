# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/16 15:00:23 by alefranc          #+#    #+#              #
#    Updated: 2022/06/15 16:18:17 by alefranc         ###   ########.fr        #
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
CFLAG = -Wall -Wextra -Werror -g3
PROJINC_FLAG = -I include

#------------------------------------#
#                LIBFT               #
#------------------------------------#

# LIBFTDIR = libft/
# LIBFT_A = $(LIBFTDIR)libft.a
#
# LIBFTINC_FLAG = -I $(LIBFTDIR)include

#------------------------------------#
#               SOURCES              #
#------------------------------------#

SRCDIR = src2/
SRCFILES =	main.c

SRC = $(addprefix $(SRCDIR), $(SRCFILES))

#------------------------------------#
#               OBJECTS              #
#------------------------------------#

OBJDIR = obj/
OBJ = $(addprefix $(OBJDIR), $(SRCFILES:.c=.o))

#------------------------------------#
#               HEADER               #
#------------------------------------#

HEADER = include/philo2.h

#------------------------------------#
#              MINILIBX              #
#------------------------------------#

# GMLX = ~/minilibx/libmlx_Linux.a -lXext -lX11 -I ~/minilibx/include/
# INC_MLX = -I ~/minilibx/include/

#------------------------------------#
#              SUMMARY               #
#------------------------------------#

LIB_ARCHIVE = $(LIBFT_A)
INC_FLAG = $(PROJINC_FLAG) $(LIBFTINC_FLAG)
LIB_PATH =
LIB_FLAG = -pthread

#------------------------------------------------------------------------------#
#                                                                              #
#                                   RULES                                      #
#                                                                              #
#------------------------------------------------------------------------------#

all: $(LIBFT_A) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAG) $(OBJ) -o $(NAME) $(LIB_ARCHIVE) $(INC_FLAG) $(LIB_PATH) $(LIB_FLAG)

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADER)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAG) -c $< -o $@ $(INC_FLAG)

$(LIBFT_A):
	make -C $(LIBFTDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
