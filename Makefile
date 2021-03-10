# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/19 16:41:59 by alagroy-          #+#    #+#              #
#    Updated: 2021/03/10 12:36:56 by alagroy-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = $(NAMENM) $(NAMEOTOOL)

NAMENM = ft_nm
NAMEOTOOL = ft_otool

SRC_PATH = ./srcs/
INCLUDE_PATH += ./includes/
INCLUDE_PATH += $(LIBDIR)includes/
LIBDIR = ./libft/
LIB = $(LIBDIR)libft.a

SRC_NM =	ft_nm.c parse_args.c read_file.c symtab.c display.c display_utils.c \
			sections.c archive.c fat.c
SRC_OTOOL = ft_otool.c parse_args.c macho.c display.c display_utils.c
SRC_SHARED = load_file.c utils.c endian.c

SRCS += $(addprefix $(SRC_PATH)nm/, $(SRC_NM))
SRCS += $(addprefix $(SRC_PATH)otool/, $(SRC_OTOOL))
SRCS += $(addprefix $(SRC_PATH)shared/, $(SRC_SHARED))

OBJ_PATH = ./.objs/
OBJS_NM = $(addprefix $(OBJ_PATH)nm/, $(SRC_NM:.c=.o))
OBJS_OTOOL = $(addprefix $(OBJ_PATH)otool/, $(SRC_OTOOL:.c=.o))
OBJS_SHARED = $(addprefix $(OBJ_PATH)shared/, $(SRC_SHARED:.c=.o))
OBJS = $(subst $(SRC_PATH),$(OBJ_PATH),$(SRCS:.c=.o))

CC = clang
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
CFLAGS += $(addprefix -I , $(INCLUDE_PATH))

HEADER += ./includes/ft_nm.h
HEADER += ./includes/ft_otool.h
HEADER += ./includes/shared.h

all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH):
	mkdir -p $@ 
	mkdir -p $@/nm 
	mkdir -p $@/otool
	mkdir -p $@/shared

$(LIB):
	make -C $(LIBDIR)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -c $< -o $@
	printf "\033[0;32m[nm-otool] Compilation [$<]                 \r\033[0m"

$(NAMENM): $(LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS_NM) $(OBJS_SHARED) -L $(LIBDIR) -lft -o $@
	printf "\n\033[0;32m[ft_nm] Linking [OK]\n"

$(NAMEOTOOL): $(LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS_OTOOL) $(OBJS_SHARED) -L $(LIBDIR) -lft -o $@
	printf "\033[0;32m[ft_otool] Linking [OK]\n"

clean:
	$(RM) -Rf $(OBJ_PATH)
	make -C $(LIBDIR) $@
	printf "\033[0;31m[nm-otool] Clean [OK]\n"

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBDIR) $@
	printf "\033[0;31m[nm-otool] Fclean [OK]\n"

re: fclean all

.PHONY: fclean clean re all
.SILENT: