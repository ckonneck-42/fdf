# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/28 11:07:45 by ckonneck          #+#    #+#              #
#    Updated: 2024/09/04 16:27:48 by ckonneck         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Source files for FdF
FdF_SRCS = main.c parsing.c coordinates.c input_and_window.c drawing.c rotation.c \
			hexa_parsing.c
FdF_OBJS = $(FdF_SRCS:.c=.o)
FdF_DEPS = $(FdF_SRCS:.c=.d)
CC = cc
LIBFT_DIR = ./libft
LIBS = -L$(LIBFT_DIR) -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR) -Imlx_linux
NAME = fdf

all: $(NAME)

$(NAME): $(FdF_OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(FdF_OBJS) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) -O3 -MMD -c $< -o $@

-include $(FdF_DEPS)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(FdF_OBJS) $(FdF_DEPS)


fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)


re: fclean all

# valgrind rule
valgrind: $(NAME)
		valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(ARGS)
# extra options: --verbose --log-file=valgrind-out.txt
# Declare phony targets
.PHONY: all libft clean fclean re valgrind