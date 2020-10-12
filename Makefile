# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flavon <flavon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/17 20:52:46 by flavon            #+#    #+#              #
#    Updated: 2020/10/12 19:21:49 by flavon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS = srcs/main.c srcs/libft/get_next_line.c srcs/libft/get_next_line_utils.c \
		srcs/libft/ft_calloc.c srcs/libft/ft_lstadd_back.c \
		srcs/libft/ft_lstadd_front.c srcs/libft/ft_lstclear.c \
		srcs/libft/ft_lstdelone.c srcs/libft/ft_lstiter.c \
		srcs/libft/ft_lstlast.c srcs/libft/ft_lstmap.c \
		srcs/libft/ft_lstnew.c srcs/libft/ft_lstsize.c \
		srcs/libft/ft_strjoin.c srcs/libft/ft_bzero.c srcs/libft/ft_strlen.c \
		srcs/libft/ft_putchar.c srcs/libft/ft_isdigit.c \
		srcs/libft/ft_atoi.c srcs/ft_init.c srcs/ft_error.c  srcs/ft_raycast.c \
		srcs/libft/ft_strdup.c srcs/ft_screen_shot.c srcs/libft/ft_putstr_fd.c \
		srcs/initialize.c srcs/initialize_utils.c srcs/ft_validate_param.c \
		srcs/libft/ft_strncmp.c srcs/keys.c srcs/keys_utils.c srcs/validate_map.c \
		srcs/ft_raycast_utils.c srcs/ft_sprite.c srcs/ft_free.c

OBJ = $(SRCS:.c=.o)

INCLUDE = srcs/cub3d.h srcs/libft/libft.h

MLX = libmlx.dylib

FLAG = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C ./minilibx_mms
	@mv ./minilibx_mms/$(MLX) . && rm -f ./minilibx_mms/$(MLX)
	@gcc $(FLAG) $(SRCS) -L. -lmlx -lm -framework OpenGL -framework AppKit -o $(NAME)

$(OBJ): %.o: %.c
	gcc $(FLAG) -c $< -o $@
	
clean:
	@$(MAKE) -C ./minilibx_mms clean
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(MLX)
	@/bin/rm -f $(NAME)
	@/bin/rm -f screenshot.bmp 

re: fclean all

.PHONY: all clean fclean re test