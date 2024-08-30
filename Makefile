# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/28 11:07:45 by ckonneck          #+#    #+#              #
#    Updated: 2024/08/29 15:44:46 by ckonneck         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Source files for FdF
FdF_SRCS = fdf.c keypress.c putpixel.c
FdF_OBJS = $(FdF_SRCS:.c=.o)
CC = cc
LIBFT_DIR = ./libft
LIBS = -L$(LIBFT_DIR) -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR) -Imlx_linux
NAME = fdf
# 'all' target
all: $(NAME)

$(NAME): $(FdF_OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(FdF_OBJS) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) -O3 -c $< -o $@
	
# 'clean' rule
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(FdF_OBJS)

# 'fclean' rule
fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

# 're' rule
re: fclean all

# Declare phony targets
.PHONY: all libft clean fclean re