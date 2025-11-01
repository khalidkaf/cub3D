NAME = cub3D

CC = cc
CFLAGS = -Werror -Wextra -Wall -MMD -g3 -fPIC

SRC_DIR = src
OBJ_DIR = objs
LIBFT_DIR = libft
MLX_DIR = minilibx-linux
# MLXFLAGS = -L$(MLX) -lmlx -lXext -lX11 -lm
#LIBFT = lib/libft/lib/libft.a

LIBFT = $(LIBFT_DIR)/libft.a
MLX_LIB = minilibx-linux/libmlx.a

# SRCS = $(shell find $(SRC_DIR) -name '*.c')
# OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

INCLUDES = -Iincludes  -I./minilibx-linux -I./$(LIBFT_DIR)

SRC = $(SRC_DIR)/main.c \
      $(SRC_DIR)/get_next_line.c \
      $(SRC_DIR)/clean.c \
      $(SRC_DIR)/collect_id.c \
      $(SRC_DIR)/collect_map_line.c \
      $(SRC_DIR)/debug_file.c \
      $(SRC_DIR)/file_utils.c \
      $(SRC_DIR)/file_utils_bis.c \
      $(SRC_DIR)/handle_spaces.c \
      $(SRC_DIR)/init.c \
      $(SRC_DIR)/map_helpers.c \
      $(SRC_DIR)/map_validation.c \
      $(SRC_DIR)/new_way.c \
      $(SRC_DIR)/parse_colors.c \
      $(SRC_DIR)/parse_textures.c \
      $(SRC_DIR)/utils_map.c \

OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
DEP = $(OBJ:.o=.d)

DEPENDS = $(OBJS:.o=.d)

LDFLAGS = -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -lXext -lX11 -lm

-include $(DEPEND)

# .PHONY: all
all: $(MLX_LIB) $(LIBFT) $(NAME)

# $(NAME): $(OBJS) $(LIBPRINTF) #$(LIBFT)
# 			$(MAKE) -C $(MLX)
# 			$(CC) $^ -o $@ $(MLXFLAGS)

$(NAME): $(OBJ)
	@echo "Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)
	@echo "✓ $(NAME) compiled!$(NC)"

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
# 	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(MLX_LIB):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR); \
	fi
		@$(MAKE) -C $(MLX_DIR) > /dev/null 2>&1

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_DIR):
	git clone https://github.com/42Paris/minilibx-linux.git $@

clean:
	rm -rf $(OBJ_DIR)
#	$(MAKE) -C lib/libft clean
fclean: clean
	rm -rf $(NAME)
	rm -rf $(_DIR)
	@$(MAKE) -C $(LIBFT_DIR) fclean > /dev/null 2>&1
#	$(MAKE) -C lib/libft fclean

re: fclean all

.PHONY:
re: all fclean all re