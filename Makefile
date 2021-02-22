# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/19 16:41:59 by alagroy-          #+#    #+#              #
#    Updated: 2021/02/19 18:26:48 by alagroy-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = $(NAMENM) $(NAMEOTOOL)

NAMENM = ft_nm
NAMEOTOOL = ft_otool

SRC_PATH = ./srcs/
OBJ_PATH = ./.objs/
INCLUDE_PATH = ./includes/ $(LIBDIR)includes/
LIBDIR = ./libft/
LIB = $(LIBDIR)libft.a

SRC_NM = ft_nm.c
SRC_OTOOL = ft_otool.c

CC = clang
CFLAGS = -Wall -Werror -Wextra
CFLAGS += $(addprefix -I , $(INCLUDE_PATH))


HEADER += $(INCLUDE_PATH)ft_nm.h
HEADER += $(INCLUDE_PATH)ft_otool.h

all: $(NAME)

$(NAMENM):

$(NAMEOTOOL):

re: fclean all

.PHONY: fclean clean re all
.SILENT: