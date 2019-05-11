# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/22 12:57:25 by mikim             #+#    #+#              #
#    Updated: 2019/05/10 08:38:24 by mikim            ###   ########.fr        #
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

VS_SRC = main.c

VS_OBJ = $(VS_SRC:.c=.o)

OCW_SRCDIR = ocw_src
OCW_OBJDIR = ocw_obj
OCW_SRCS = $(addprefix $(OCW_SRCDIR)/, $(OCW_SRC))
OCW_OBJS = $(addprefix $(OCW_OBJDIR)/, $(OCW_OBJ))

VS_SRCDIR = vs_src
VS_OBJDIR = vs_obj
VS_SRCS = $(addprefix $(VS_SRCDIR)/, $(VS_SRC))
VS_OBJS = $(addprefix $(VS_OBJDIR)/, $(VS_OBJ))

LIBDIR = lib
LIBFTDIR = $(LIBDIR)/libft
MLXDIR = $(LIBDIR)/mlx

MLX = -L $(MLXDIR) -lmlx -framework OpenGL -framework Appkit
LIBFT = -L $(LIBFTDIR) -lft
LIB = $(LIBFT) $(MLX)

HEADER = -I includes -I $(LIBFTDIR)/includes -I $(MLXDIR)

CC = gcc
CC++ = g++ -std=c++17
CFLAG = -c
GFLAG = -g
WFLAG = -Wall -Wextra -Werror

OCW = ocw
VS = visualizer

.PHONY: all clean fclean re
.SUFFIXES: .c .o

all: $(OCW) $(VS)

$(OCW_OBJDIR)/%.o: $(OCW_SRCDIR)/%.cpp
	@mkdir -p $(OCW_OBJDIR)
	@$(CC++) $(CFLAG) $(WFLAG) $(HEADER) $< -o $@

$(OCW): $(OCW_OBJS)
	@$(CC++) $(OCW_OBJS) -o $@
	@echo "\x1b[32;1m[$(OCW) - Make Completed]\x1b[0m"

$(VS_OBJDIR)/%.o: $(VS_SRCDIR)/%.c
	@mkdir -p $(VS_OBJDIR)
	@$(CC) $(CFLAG) $(WFLAG) $(HEADER) $< -o $@

$(VS): $(VS_OBJS)
	@make -C $(LIBFTDIR)
	@make -C $(MLXDIR)
	@$(CC) $(VS_OBJS) $(LIB) -o $@
	@echo "\x1b[32;1m[$(VS) - Make Completed]\x1b[0m"

clean:
	@/bin/rm -rf $(OCW_OBJDIR) $(VS_OBJDIR)
	@echo "\x1b[35;1m[$(OCW) - clean]\x1b[0m"

fclean: clean
	@/bin/rm -f $(OCW) $(VS)
	@echo "\x1b[31m[$(OCW) - fclean]\x1b[0m"

re: fclean all
