# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/22 12:57:25 by mikim             #+#    #+#              #
#    Updated: 2019/04/14 10:06:40 by mikim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                               Mingyun Kim    #
#                                            https://www.github.com/mikim42    #
# **************************************************************************** #

# TEMPLATE FOR NOW FEB.22.19

OCW_SRC = main.cpp\
		  ocw.cpp\
		  players.cpp

OCW_OBJ = $(OCW_SRC:.cpp=.o)

VIS_SRC = main.c

VIS_OBJ = $(VIS_SRC:.c=.o)

OCW_SRCDIR = ocw_src
OCW_OBJDIR = ocw_obj

OCW_SRCS = $(addprefix $(OCW_SRCDIR)/, $(OCW_SRC))
OCW_OBJS = $(addprefix $(OCW_OBJDIR)/, $(OCW_OBJ))

MLX = -L $(MLXDIR) -lmlx -framework OpenGL -framework Appkit
HEADER = -I includes 

CC = gcc
CC++ = g++ -std=c++17
CFLAG = -c
WFLAG = -Wall -Wextra -Werror

NAME = ocw
VIS = visualizer

.PHONY: all clean fclean re
.SUFFIXES: .c .o

all: $(NAME)

$(OCW_OBJDIR)/%.o: $(OCW_SRCDIR)/%.cpp
	@mkdir -p $(OCW_OBJDIR)
	@$(CC++) $(CFLAG) $(WFLAG) $(HEADER) $< -o $@

$(NAME): $(OCW_OBJS)
	@$(CC++) $(OCW_OBJS) -o $@
	@echo "\x1b[32;1m[$(NAME) - Make Completed]\x1b[0m"

clean:
	@/bin/rm -rf $(OCW_OBJDIR) $(VIS_OBJDIR)
	@echo "\x1b[35;1m[$(NAME) - clean]\x1b[0m"

fclean: clean
	@/bin/rm -f $(NAME) $(VIS)
	@echo "\x1b[31m[$(NAME) - fclean]\x1b[0m"

re: fclean all
