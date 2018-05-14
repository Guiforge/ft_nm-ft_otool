# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/23 09:03:46 by gpouyat           #+#    #+#              #
#    Updated: 2018/05/14 09:17:21 by gpouyat          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

CC = gcc

FLAGS = -Wall -Wextra -Werror

ifeq ($(DEV),yes)
    FLAGS		+= -g
endif

ifeq ($(SAN),yes)
    FLAGS		+= -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
endif

NAME_NM = ft_nm
NAME_OTOOL = ft_otool

C_NO = \033[0m
C_G = \033[0;32m
C_Y = \033[1;33m
C_B = \033[1;34m
C_C = \033[1;36m
C_R = \033[1;31m

SRC_PATH_NM = ./srcs/ft_nm
SRC_PATH_OTOOL = ./srcs/ft_otool
SRC_PATH_MISC = ./srcs/misc
LIB_PATH = ./libft
INC_PATH = ./includes
INC_LIB = ./libft/includes
OBJ_PATH = ./obj
OBJ_PATH_NM = ./obj/nm
OBJ_PATH_OTOOL = ./obj/otool
OBJ_PATH_MISC = ./obj/misc

SRC_NAME_NM = main.c error.c handle_64.c find_seg_sect_name.c

SRC_NAME_OTOOL = main.c

SRC_NAME_MISC = map_file.c secure_add.c exec_handler.c get_header.c

OBJ_NAME_NM = $(SRC_NAME_NM:.c=.o)
OBJ_NAME_OTOOL = $(SRC_NAME_OTOOL:.c=.o)
OBJ_NAME_MISC = $(SRC_NAME_MISC:.c=.o)
LIB_NAME = libft.a

SRC_NM = $(addprefix $(SRC_PATH_NM)/, $(SRC_NAME_NM))
SRC_OTOOL = $(addprefix $(SRC_PATH_OTOOL)/, $(SRC_NAME_OTOOL))
SRC_MISC = $(addprefix $(SRC_PATH_MISC)/, $(SRC_NAME_MISC))
LIB = $(addprefix $(LIB_PATH)/, $(LIB_NAME))
OBJ_NM = $(addprefix $(OBJ_PATH_NM)/,$(OBJ_NAME_NM))
OBJ_OTOOL = $(addprefix $(OBJ_PATH_OTOOL)/,$(OBJ_NAME_OTOOL))
OBJ_MISC = $(addprefix $(OBJ_PATH_MISC)/,$(OBJ_NAME_MISC))

all: $(NAME_NM) $(NAME_OTOOL)

$(NAME_NM): $(LIB) $(OBJ_MISC) $(OBJ_NM)
	$(CC) -o $(NAME_NM) $(FLAGS) $(OBJ_NM) $(OBJ_MISC) $(LIB)
	@printf "$(C_G)%-20s\t$(C_Y)Compilation\t$(C_G)[ OK ✔ ]$(C_NO)\n\n" $(NAME_NM)

$(NAME_OTOOL): $(LIB) $(OBJ_MISC) $(OBJ_OTOOL)
	$(CC) -o $(NAME_OTOOL) $(FLAGS) $(OBJ_OTOOL) $(OBJ_MISC) $(LIB)
	@printf "$(C_G)%-20s\t$(C_Y)Compilation\t$(C_G)[ OK ✔ ]$(C_NO)\n\n" $(NAME_OTOOL)

$(OBJ_PATH_NM)/%.o: $(SRC_PATH_NM)/%.c
	@mkdir -p $(OBJ_PATH) $(OBJ_PATH_NM)
	$(CC) $(FLAGS) -o $@ -c $< -I $(INC_PATH) -I $(INC_LIB)

$(OBJ_PATH_OTOOL)/%.o: $(SRC_PATH_OTOOL)/%.c
	@mkdir -p $(OBJ_PATH) $(OBJ_PATH_OTOOL)
	$(CC) $(FLAGS) -o $@ -c $< -I $(INC_PATH) -I $(INC_LIB)

$(OBJ_PATH_MISC)/%.o: $(SRC_PATH_MISC)/%.c
	@mkdir -p $(OBJ_PATH) $(OBJ_PATH_MISC)
	$(CC) $(FLAGS) -o $@ -c $< -I $(INC_PATH) -I $(INC_LIB)

$(LIB):
	@make -C $(LIB_PATH) DEV=$(DEV) SAN=$(SAN)

miniclean:
	@rm -rf $(OBJ_NM)
	@rm -rf $(OBJ_OTOOL)
	@printf "$(C_B)%-20s\t$(C_Y)Cleaning obj\t$(C_G)[ OK ✔ ]$(C_NO)\n" $(NAME_NM) $(NAME_OTOOL)

clean:
	@rm -rf $(OBJ_NM)
	@rm -rf $(OBJ_OTOOL)
	@make -C $(LIB_PATH) clean
	@printf "$(C_B)%-20s\t$(C_Y)Cleaning obj\t$(C_G)[ OK ✔ ]$(C_NO)\n" $(NAME_NM) $(NAME_OTOOL)

fclean:
	@rm -rf ./obj $(NAME_NM) $(NAME_OTOOL)
	@make -C $(LIB_PATH) fclean
	@printf "$(C_B)%-20s\t$(C_Y)Cleaning binary\t$(C_G)[ OK ✔ ]$(C_NO)\n" $(NAME_NM) $(NAME_OTOOL)

minire: clean all

re: fclean all