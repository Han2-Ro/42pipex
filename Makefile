# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/24 22:50:02 by hrother           #+#    #+#              #
#    Updated: 2023/11/29 00:23:40 by hannes           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -g -Wall -Wextra -Werror
SRC_DIR = src
OBJ_DIR = objs
SRCS = *.c
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))
NAME = pipex

all: $(NAME) $(NAME_BONUS)

$(NAME): $(OBJS)
	# make -C ./libft
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) #-L./libft -lft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	# make clean -C ./libft
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)

fclean: clean
	# make fclean -C ./libft
	rm -f $(NAME)
	rm -f $(NAME_BONUS)

re: fclean all

.PHONY: all bonus clean fclean re