/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 14:43:32 by kkafmagh          #+#    #+#             */
/*   Updated: 2025/11/01 20:35:24 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "mlx_int.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# define SUCCESS 1
# define ERROR 0

# define RGB_MIN 0
# define RGB_MAX 255

# define MIN_FILENAME_LEN 4
# define CUB_EXTENSION ".cub"

# define MOVE_SPEED 0.02
# define ROT_SPEED 0.02

typedef struct s_color
{
	int					r;
	int					g;
	int					b;

}						t_color;

typedef struct s_map_line
{
	char				*line;
	struct s_map_line	*next;
}						t_map_line;

typedef struct s_map_data
{
	t_map_line			*head;
	t_map_line			*tail;
}						t_map_data;

typedef struct s_cell_info
{
	int					x;
	int					y;
	char				c;
}						t_cell_info;

typedef struct s_keys
{
	int					up;
	int					down;
	int					left;
	int					right;
	int					rotate_left;
	int					rotate_right;
}						t_keys;

typedef struct s_texture
{
	void				*img;
	char				*addr;
	int					width;
	int					height;
	int					bpp;
	int					line_length;
	int					endian;
}						t_texture;

typedef struct s_image
{
	void				*img;
	char				*addr;
	int					bpp;
	int					line_length;
	int					endian;
	int					width;
	int					height;
}						t_image;

typedef struct s_player
{
	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
	char				dir;
}						t_player;

typedef struct s_pos_player
{
	float				dir_x;
	float				dir_y;
	float				plane_x;
	float				plane_y;
}						t_pos_player;

typedef struct s_dist
{
	double				side_dist_x;
	double				side_dist_y;
	double				delta_dist_x;
	double				delta_dist_y;
	int					side;
	int					map_x;
	int					map_y;
	int					step_x;
	int					step_y;
	int					hit;
}						t_dist;

typedef struct s_data
{
	void				*connection;
	void				*window;
	char				**map;
	int					map_width;
	int					map_height;
	char				*tex_north_path;
	char				*tex_south_path;
	char				*tex_west_path;
	char				*tex_east_path;
	t_map_data			map_data;
	t_color				floor_color;
	t_color				ceiling_color;
	t_image				img;
	t_player			player;
	t_keys				keys;
	t_texture			tex_north;
	t_texture			tex_south;
	t_texture			tex_east;
	t_texture			tex_west;
}						t_data;

int						map_height(char **map);
char					*ft_strchr(const char *str, int c);
void					*ft_calloc(size_t elementCount, size_t elementSize);
char					*ft_strjoin1(char *s1, char *s2);
int						ft_strlen(const char *str);
void					*ft_memcpy(void *dest, const void *src,
							size_t numBytes);
char					*extract_line(char *stock);
char					*update_stock(char *stock);
char					*get_next_line(int fd);
char					*skip_whitespace(const char *str);
int						is_empty_or_comment(const char *line);
int						process_identifier_line(t_data *data, char *line);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						parse_texture_line(t_data *data, char *line);
int						parse_color_line(t_data *data, char *line);
char					*ft_strtrim(char const *s1, char const *set);
int						print_map_error(const char *msg);
char					*ft_strdup(char *src);
int						ft_strcmp(const char *s1, const char *s2);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
int						ft_iswhitespace(char c);
int						extension_check(const char *filename);
int						has_xpm_extension(char *path);
int						open_file(const char *filename);
char					*skip_whitespace(const char *str);
int						is_empty_or_comment(const char *line);
int						new_parse_file(t_data *data, const char *filename);
int						init_data(t_data *data);
int						collect_identifiers(t_data *data, int fd);
int						process_identifier_line(t_data *data, char *line);
int						process_single_identifier_line(t_data *data, int fd,
							int *count);
int						parse_texture_line(t_data *data, char *line);
int						handle_texture(char **texture, char *path,
							const char *id);
int						is_valid_rgb_value(const char *str);
int						is_valid_color_format(const char *line);
int						check_color_input(t_data *data, char *line);
int						assign_color_values(t_data *data, char identifier,
							t_color color);
int						parse_color_line(t_data *data, char *line);
t_map_line				*create_map_line(char *line_content);
void					add_map_line(t_map_data *map, t_map_line *new_line);
int						collect_map_lines(t_map_data *map, int fd);
int						print_map_error(const char *msg);
int						is_player(char c);
int						is_valid_map_char(char c);
int						get_map_height(t_map_data *map_data);
int						get_map_width(t_map_data *map_data);
int						is_only_spaces(char *line);
char					get_map_at_index(t_map_data *map_data, int x, int y);
t_map_line				*get_map_line_at(t_map_data *map, int y);
int						find_valid_lines(t_map_data *map, int *first,
							int *last);
int						check_map_no_empty_lines_in_middle(t_map_data *map);
int						has_bad_neighbor(t_map_data *map, int x, int y);
int						validate_map(t_data *data);
int						is_border(int x, int y, int width, int height);
int						error_and_debug(const char *msg, int x, int y, char c);
void					free_data(t_data *data);
void					print_textures(t_data *data);
void					print_colors(t_data *data);
void					print_map(t_data *data);
int						ft_isdigit(int c);
int						ft_atoi(const char *str);
int						is_in_set(char c, char const *set);
int						ft_iswhitespace(char c);
int						ft_strcmp(const char *s1, const char *s2);

#endif
