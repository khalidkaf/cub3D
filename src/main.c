#include "cub3d.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*tmp;

	tmp = s;
	while (n)
	{
		*tmp = (unsigned char)c;
		tmp++;
		n--;
	}
	return (s);
}

int	file_name(char **argv)
{
	int	len;

	len = ft_strlen(argv[1]);
	if (len < 4)
		return (0);
	if (argv[1][ft_strlen(argv[1]) - 1] != 'b' || argv[1][ft_strlen(argv[1])
		- 2] != 'u' || argv[1][ft_strlen(argv[1]) - 3] != 'c'
		|| argv[1][ft_strlen(argv[1]) - 4] != '.')
		return (0);
	return (1);
}

int	file_exists(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

void	pos_start_n(t_player *player, int i, int j)
{
	player->pos_y = i + 0.5;
	player->pos_x = j + 0.5;
	player->dir_x = 0;
	player->dir_y = -1;
	player->plane_x = 0.66;
	player->plane_y = 0;
}

void	pos_start_s(t_player *player, int i, int j)
{
	player->pos_y = i + 0.5;
	player->pos_x = j + 0.5;
	player->dir_x = 0;
	player->dir_y = 1;
	player->plane_x = -0.66;
	player->plane_y = 0;
}

void	pos_start_e(t_player *player, int i, int j)
{
	player->pos_y = i + 0.5;
	player->pos_x = j + 0.5;
	player->dir_x = 1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.66;
}
void	pos_start_w(t_player *player, int i, int j)
{
	player->pos_y = i + 0.5;
	player->pos_x = j + 0.5;
	player->dir_x = -1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = -0.66;
}

void	starter(t_player *player, t_map_data *map)
{
	int			i;
	int			j;
	t_map_line	*current;

	current = map->head;
	i = 0;
	j = 0;
	while (current)
	{
		j = 0;
		while (current->line[j])
		{
			if (current->line[j] == 'N')
				return (pos_start_n(player, i, j));
			else if (current->line[j] == 'S')
				return (pos_start_s(player, i, j));
			else if (current->line[j] == 'E')
				return (pos_start_e(player, i, j));
			else if (current->line[j] == 'W')
				return (pos_start_w(player, i, j));
			j++;
		}
		j = 0;
		i++;
		current = current->next;
	}
}

void	flood_fill(char **map, int i, int j, int rows, int cols)
{
	if (i < 0 || j < 0 || i >= rows || j >= cols)
		return ;
	if (map[i][j] == '1' || map[i][j] == 'Z')
	{
		return ;
	}
	map[i][j] = 'Z';
	flood_fill(map, i + 1, j, rows, cols);
	flood_fill(map, i - 1, j, rows, cols);
	flood_fill(map, i, j + 1, rows, cols);
	flood_fill(map, i, j - 1, rows, cols);
}

int	handle_key_press(int keycode, t_data *data)
{
	// printf("Key pressed: %d\n", keycode); // ✅ Ajoute ceci
	if (keycode == XK_w)
		data->keys.up = 1;
	if (keycode == XK_s)
		data->keys.down = 1;
	if (keycode == XK_a)
		data->keys.left = 1;
	if (keycode == XK_d)
		data->keys.right = 1;
	if (keycode == XK_Left)
		data->keys.rotate_left = 1;
	if (keycode == XK_Right)
		data->keys.rotate_right = 1;
	if (keycode == XK_Escape)
	{
		free_data(data);
		exit(0);
	}
	return (0);
}

int	handle_key_release(int keycode, t_data *data)
{
	if (keycode == XK_w)
		data->keys.up = 0;
	if (keycode == XK_s)
		data->keys.down = 0;
	if (keycode == XK_a)
		data->keys.left = 0;
	if (keycode == XK_d)
		data->keys.right = 0;
	if (keycode == XK_Left)
		data->keys.rotate_left = 0;
	if (keycode == XK_Right)
		data->keys.rotate_right = 0;
	return (0);
}

void	rotate_player(t_player *player, float angle)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(angle) - player->dir_y * sin(angle);
	player->dir_y = old_dir_x * sin(angle) + player->dir_y * cos(angle);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(angle) - player->plane_y
		* sin(angle);
	player->plane_y = old_plane_x * sin(angle) + player->plane_y * cos(angle);
}

int	is_valid_position(t_data *data, int x, int y)
{
	if (y < 0 || y >= data->map_height)
		return (0);
	if (x < 0 || x >= (int)ft_strlen(data->map[y]))
		return (0);
	if (data->map[y][x] == '1')
		return (0);
	return (1);
}

void	update_player(t_data *data)
{
	t_player	*p;
	int			new_x;
	int			new_y;

	p = &data->player;
	// Avancer
	if (data->keys.up)
	{
		new_x = (int)(p->pos_x + p->dir_x * MOVE_SPEED);
		new_y = (int)(p->pos_y + p->dir_y * MOVE_SPEED);
		if (is_valid_position(data, new_x, (int)p->pos_y))
			p->pos_x += p->dir_x * MOVE_SPEED;
		if (is_valid_position(data, (int)p->pos_x, new_y))
			p->pos_y += p->dir_y * MOVE_SPEED;
	}
	// Reculer
	if (data->keys.down)
	{
		new_x = (int)(p->pos_x - p->dir_x * MOVE_SPEED);
		new_y = (int)(p->pos_y - p->dir_y * MOVE_SPEED);
		if (is_valid_position(data, new_x, (int)p->pos_y))
			p->pos_x -= p->dir_x * MOVE_SPEED;
		if (is_valid_position(data, (int)p->pos_x, new_y))
			p->pos_y -= p->dir_y * MOVE_SPEED;
	}
	// Strafe gauche (A)
	if (data->keys.left)
	{
		new_x = (int)(p->pos_x - p->plane_x * MOVE_SPEED);
		new_y = (int)(p->pos_y - p->plane_y * MOVE_SPEED);
		if (is_valid_position(data, new_x, (int)p->pos_y))
			p->pos_x -= p->plane_x * MOVE_SPEED;
		if (is_valid_position(data, (int)p->pos_x, new_y))
			p->pos_y -= p->plane_y * MOVE_SPEED;
	}
	// Strafe droite (D)
	if (data->keys.right)
	{
		new_x = (int)(p->pos_x + p->plane_x * MOVE_SPEED);
		new_y = (int)(p->pos_y + p->plane_y * MOVE_SPEED);
		if (is_valid_position(data, new_x, (int)p->pos_y))
			p->pos_x += p->plane_x * MOVE_SPEED;
		if (is_valid_position(data, (int)p->pos_x, new_y))
			p->pos_y += p->plane_y * MOVE_SPEED;
	}
	// Rotation
	if (data->keys.rotate_left)
		rotate_player(p, -ROT_SPEED);
	if (data->keys.rotate_right)
		rotate_player(p, ROT_SPEED);
}

// int	handle_esc(int key, t_data *data)
// {
// 	if (key == XK_Escape)
// 	{
// 		printf("=====================TEST=====================\n");
// 		exit(1);
// 	}
// 	mlx_clear_window(data->connection, data->window);
// 	mlx_put_image_to_window(data->connection, data->window, data->img.img,
// 		data->player.pos_x, data->player.pos_y);
// 	return (1);
// }

int	check_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
	{
		i++;
	}
	return (i);
}

void	put_pixel(char *addr, int x, int y, int color, int bits_per_pixel,
		int line_length)
{
	char	*dst;

	dst = addr + (y * line_length + x * (bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= 1024 || y >= 512)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	render_frame(t_data *param)
{
	t_data		*data;
	int			x;
	int			y;
	int			x2;
	char		*tex_pixel;
	t_texture	*tex;
	int			color;
	int			hit;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			side;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	double		perp_wall_dist;
	double		wall_x;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_x;
	int			tex_y;
	int			d;
	int			ceiling_color;
	int			floor_color;

	data = (t_data *)param;
	update_player(data);
	// Convertir les couleurs RGB en format entier (0xRRGGBB)
	ceiling_color = (data->ceiling_color.r << 16) | (data->ceiling_color.g << 8) | data->ceiling_color.b;
	floor_color = (data->floor_color.r << 16) | (data->floor_color.g << 8) | data->floor_color.b;
	// Effacer l'écran : plafond + sol
	y = 0;
	while (y < 512)
	{
		x2 = 0;
		while (x2 < 1024)
		{
			if (y < 512 / 2)
				my_mlx_pixel_put(&data->img, x2, y, ceiling_color);
			else
				my_mlx_pixel_put(&data->img, x2, y, floor_color);
			x2++;
		}
		y++;
	}
	// Raycasting pour chaque colonne
	x = 0;
	while (x < 1024)
	{
		camera_x = 2 * x / (double)1024 - 1;
		ray_dir_x = data->player.dir_x + data->player.plane_x * camera_x;
		ray_dir_y = data->player.dir_y + data->player.plane_y * camera_x;
		map_x = (int)data->player.pos_x;
		map_y = (int)data->player.pos_y;
		delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
		delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (data->player.pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - data->player.pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (data->player.pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - data->player.pos_y) * delta_dist_y;
		}
		// DDA
		hit = 0;
		while (!hit)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			// Protection contre accès hors map - vérifier AVANT l'accès
			if (map_y < 0 || map_y >= data->map_height)
				break ;
			if (map_x < 0 || map_x >= (int)ft_strlen(data->map[map_y]))
				break ;
			if (data->map[map_y][map_x] == '1')
				hit = 1;
		}
		// Si on n'a pas touché de mur, passer à la colonne suivante
		if (!hit)
		{
			x++;
			continue ;
		}
		// Choix texture selon direction du mur
		if (side == 0)
			tex = (ray_dir_x > 0) ? &data->tex_west : &data->tex_east;
		else
			tex = (ray_dir_y > 0) ? &data->tex_north : &data->tex_south;
		// Distance projetée et hauteur de mur
		perp_wall_dist = (side == 0) ? (side_dist_x
				- delta_dist_x) : (side_dist_y - delta_dist_y);
		line_height = (int)(512 / perp_wall_dist);
		if (line_height == 0)
			line_height = 1;
		draw_start = -line_height / 2 + 512 / 2;
		draw_end = line_height / 2 + 512 / 2;
		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= 512)
			draw_end = 512 - 1;
		// Vérification texture valide
		if (!tex || !tex->addr || tex->width <= 0 || tex->height <= 0
			|| tex->line_length <= 0)
		{
			y = draw_start;
			while (y <= draw_end)
			{
				my_mlx_pixel_put(&data->img, x, y, 0xFF00FF);
				y++;
			}
			x++;
			continue ;
		}
		// Coordonnée X de texture
		wall_x = (side == 0) ? data->player.pos_y + perp_wall_dist
			* ray_dir_y : data->player.pos_x + perp_wall_dist * ray_dir_x;
		wall_x -= floor(wall_x);
		tex_x = (int)(wall_x * tex->width);
		if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
			tex_x = tex->width - tex_x - 1;
		// 🔒 PROTECTION : s'assurer que tex_x est dans les limites
		if (tex_x < 0)
			tex_x = 0;
		if (tex_x >= tex->width)
			tex_x = tex->width - 1;
		// Dessin vertical du mur
		y = draw_start;
		while (y <= draw_end)
		{
			d = y * 256 - 512 * 128 + line_height * 128;
			tex_y = ((d * tex->height) / line_height) / 256;
			// 🔒 PROTECTION CRITIQUE : borner tex_y
			if (tex_y < 0)
				tex_y = 0;
			if (tex_y >= tex->height)
				tex_y = tex->height - 1;
			// 🔒 VÉRIFICATION FINALE avant accès mémoire
			if (tex_y >= 0 && tex_y < tex->height && tex_x >= 0
				&& tex_x < tex->width)
			{
				tex_pixel = tex->addr + (tex_y * tex->line_length + tex_x
						* (tex->bpp / 8));
				color = *(unsigned int *)tex_pixel;
				my_mlx_pixel_put(&data->img, x, y, color);
			}
			y++;
		}
		x++;
	}
	// Affichage final
	mlx_put_image_to_window(data->connection, data->window, data->img.img, 0,
		0);
	return (0);
}

int	close_window(t_data *data)
{
	free_data(data);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_map_line	*current;
	int			i;

	// int		fd;
	// char	**mappy;
	if (argc != 2)
	{
		printf("Usage: %s <map_file.cub>\n", argv[0]);
		return (1);
	}
	if (extension_check(argv[1]) == ERROR)
		return (1);
	ft_memset(&data, 0, sizeof(t_data));
	if (init_data(&data) == ERROR)
		return (1);
	if (new_parse_file(&data, argv[1]) == ERROR)
	{
		printf("Parsing failed.\n");
		get_next_line(-1);
		free_data(&data);
		return (1);
	}
	data.map_width = get_map_width(&data.map_data);
	data.map_height = get_map_height(&data.map_data);
	printf("Textures:\n");
	print_textures(&data);
	// print_colors(&data);
	// print_map(&data);
	// return (free_data(&data), 0);
	// ft_memset(&data, 0, sizeof(t_data));
	// fd = open(argv[1], O_RDONLY);
	// if (fd < 0)
	// {
	// 	perror("Erreur lors de l'ouverture du fichier");
	// 	return (1);
	// }
	// mappy = parse_map(fd);
	// if (!mappy)
	if (!data.map_data.head)
	{
		printf(/* stderr,  */ "Erreur lors du parsing de la map\n");
		free_data(&data);
		return (1);
	}
	// data.map = mappy;
	// while(data.map_data.head->line)
	// {
	// 	printf("%s \n",data.map_data.head->line);
	// }
	i = 0;
	data.map = malloc(sizeof(char *) * (data.map_height + 1));
	if (!data.map)
	{
		free_data(&data);
		return (perror("malloc data.map"), ERROR);
	}
	current = data.map_data.head;
	while (current)
	{
		data.map[i] = ft_strdup(current->line);
		if (!data.map[i])
		{
			while (i-- > 0)
				free(data.map[i]);
			free(data.map);
			free_data(&data);
			return (perror("ft_strdup"), ERROR);
		}
		current = current->next;
		i++;
	}
	data.map[i] = NULL;
	// i = 0;
	// while(data.map[i])
	// {
	// 	printf("****************%s", data.map[i]);
	// 	i++;
	// }
	starter(/* data.map,  */ &data.player, &data.map_data);
	// printf("8888888888888888888888888888888888888888888888\n");
	// printf("Player position: x = %f, y = %f\n", data.player.pos_x,
	// 	data.player.pos_y);
	data.connection = mlx_init();
	if (!data.connection)
		return (1);
	data.window = mlx_new_window(data.connection, 1024, 512, "Cub3d");
	if (!data.window)
		return (1);
	// printf("******%s*******\n", data.tex_north.addr);
	if (!file_exists("north.xpm") || !file_exists("south.xpm")
		|| !file_exists("east.xpm") || !file_exists("west.xpm"))
	{
		printf("Erreur: fichiers .xpm manquants\n");
		free_data(&data);
		return (1);
	}
	// Charger wall.xpm
	data.tex_north.img = mlx_xpm_file_to_image(data.connection,
			data.tex_north_path, &data.tex_north.width, &data.tex_north.height);
	data.tex_south.img = mlx_xpm_file_to_image(data.connection,
			data.tex_south_path, &data.tex_south.width, &data.tex_south.height);
	data.tex_east.img = mlx_xpm_file_to_image(data.connection,
			data.tex_east_path, &data.tex_east.width, &data.tex_east.height);
	data.tex_west.img = mlx_xpm_file_to_image(data.connection,
			data.tex_west_path, &data.tex_west.width, &data.tex_west.height);
	if (!data.tex_north.img || !data.tex_south.img || !data.tex_east.img
		|| !data.tex_west.img)
	{
		printf("Erreur : impossible de charger wall.xpm\n");
		free_data(&data);
		return (1);
	}
	// Récupérer les infos de l’image texture
	data.tex_north.addr = mlx_get_data_addr(data.tex_north.img,
			&data.tex_north.bpp, &data.tex_north.line_length,
			&data.tex_north.endian);
	data.tex_south.addr = mlx_get_data_addr(data.tex_south.img,
			&data.tex_south.bpp, &data.tex_south.line_length,
			&data.tex_south.endian);
	data.tex_east.addr = mlx_get_data_addr(data.tex_east.img,
			&data.tex_east.bpp, &data.tex_east.line_length,
			&data.tex_east.endian);
	data.tex_west.addr = mlx_get_data_addr(data.tex_west.img,
			&data.tex_west.bpp, &data.tex_west.line_length,
			&data.tex_west.endian);
	if (!data.tex_north.img || !data.tex_south.img || !data.tex_east.img
		|| !data.tex_west.img)
	{
		printf("Erreur : mlx_get_data_addr a echoue\n");
		free_data(&data);
		return (1);
	}
	data.img.img = mlx_new_image(data.connection, 1024, 512);
	if (!data.img.img)
		return (1);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bpp,
			&data.img.line_length, &data.img.endian);
	// mlx_hook(data.window, 2, 1L << 0, handle_esc, &data);
	mlx_hook(data.window, 2, 1L << 0, handle_key_press, &data); // Key press
	// printf("******************************\n");
	// printf("%d\n", data.floor_color.r);
	// printf("%d\n", data.floor_color.g);
	// printf("%d\n", data.floor_color.b);
	// printf("************%s *****\n", data.img.addr);
	mlx_hook(data.window, 3, 1L << 1, handle_key_release, &data); // Key release
	mlx_loop_hook(data.connection, render_frame, &data);
	mlx_hook(data.window, 17, 0, close_window, &data); // Key release
	// printf("before\n");
	mlx_loop(data.connection);
	// printf("after\n");
	return (0);
}
