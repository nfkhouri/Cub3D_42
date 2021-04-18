NAME =		cub3D
GNL = get_next_line

SRC_DIR = 	srcs
MLX_DIR = 	minilibx-linux
OBJS_DIR =	objs
GNL_DIR = GNL

CC =		clang -g -fsanitize=address
FLAGS_CC =	-Wall -Wextra -Werror
FLAGS_MLX =	-lm -lbsd -lX11 -lXext -lmlx
					
MLX =		$(MLX_DIR)/libmlx.a
SRCS =		$(SRC_DIR)/main.c $(SRC_DIR)/close.c $(SRC_DIR)/ft_mlx_pixel_put.c \
				$(SRC_DIR)/ft_empty_circle.c $(SRC_DIR)/ft_square.c $(SRC_DIR)/ft_line.c \
				$(SRC_DIR)/ft_filled_circle.c $(SRC_DIR)/key_press.c $(SRC_DIR)/ft_init.c \
				$(SRC_DIR)/ft_move.c $(SRC_DIR)/ft_putendl_fd.c $(SRC_DIR)/ft_check_args.c \
				$(GNL_DIR)/$(GNL).c $(GNL_DIR)/$(GNL)_utils.c  $(SRC_DIR)/ft_strncmp.c  \
				$(SRC_DIR)/ft_map.c $(SRC_DIR)/ft_isdigit.c $(SRC_DIR)/ft_atoi.c \
				$(SRC_DIR)/ft_strtrim.c $(SRC_DIR)/ft_split.c $(SRC_DIR)/ft_strchr.c \
				$(SRC_DIR)/ft_resolution.c $(SRC_DIR)/ft_strlen.c $(SRC_DIR)/ft_substr.c \
				$(SRC_DIR)/ft_strdup.c $(SRC_DIR)/ft_colors.c $(SRC_DIR)/ft_textures.c \
				$(SRC_DIR)/ft_input.c $(SRC_DIR)/ft_render.c $(SRC_DIR)/raycasting.c \
				$(SRC_DIR)/other_functions.c $(SRC_DIR)/textures.c $(SRC_DIR)/sprites.c \
				$(SRC_DIR)/bmp.c $(SRC_DIR)/ft_bzero.c


HEAD =		-I ./$(NAME).h -I ./$(GNL).h -I ./$(MLX_DIR) -L ./$(MLX_DIR)

OBJS =		$(patsubst $(SRC_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS)) #subst in directory

RM =		/bin/rm -rf

all: $(NAME)

$(NAME): $(MLX) $(OBJS) #$@ means the output file will be ./cub3D instead of ./a.out
	$(CC) $(FLAGS_CC) $(OBJS) $(HEAD) $(FLAGS_MLX) $(MLX) -o $@

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(HEAD) -c $< -o $@

$(MLX):
	make -C $(MLX_DIR)

clean:
	make clean -C $(MLX_DIR)
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: re
	./cub3D $(ARGS)

debug: $(MLX) $(OBJS)
	$(CC) -g $(FLAGS_MLX) $(FLAGS_CC) $(OBJS) $(HEAD) $(MLX) -o "cub3D_debug"

.PONY: all clean fclean re
