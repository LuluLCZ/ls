# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/08 11:29:27 by llacaze           #+#    #+#              #
#    Updated: 2018/01/25 17:52:49 by llacaze          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CC = clang

OPTIONS = -c

CFLAGS = -Wall -Wextra -Werror

RM = rm -Rfv

SRC = 		main.c 	\
			recursive.c\
			init_list.c	\
			infos.c		\
			parse.c		\
			aff.c		\
			ft_swapc.c	\
			sort.c		\
			recup_names.c	\
			sort_args.c		\
			color.c	\
			error.c\
			norm_one.c\
			norm_two.c\
			norm_three.c\
			norm_four.c\
			lst_utils.c\
			lst_utils_two.c\
			norm_five.c

OBJ = $(SRC:.c=.o)

HEAD_DIR = ./libft/

all: $(NAME)

$(NAME): $(OBJ) Makefile ft_ls.h
	@$(CC) $(CFLAGS) $(OPTIONS) $(SRC)
	@cd $(HEAD_DIR) && $(MAKE)
	@$(CC) $(OBJ) ./libft/libft.a -o $(NAME)

clean:
	@$(RM) $(OBJ)
	@cd $(HEAD_DIR) && $(MAKE) $@

fclean: clean
	@$(RM) $(OBJ)
	@$(RM) $(NAME)
	@make -C $(HEAD_DIR) fclean

re: fclean all

.PHONY : all clean fclean re
