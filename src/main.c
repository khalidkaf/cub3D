/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:35:56 by kkafmagh          #+#    #+#             */
/*   Updated: 2025/11/03 12:21:43 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_text(t_data *data)
{
	data->tex_north.img = mlx_xpm_file_to_image(data->connection,
			data->tex_north_path, &data->tex_north.width,
			&data->tex_north.height);
	data->tex_south.img = mlx_xpm_file_to_image(data->connection,
			data->tex_south_path, &data->tex_south.width,
			&data->tex_south.height);
	data->tex_east.img = mlx_xpm_file_to_image(data->connection,
			data->tex_east_path, &data->tex_east.width, &data->tex_east.height);
	data->tex_west.img = mlx_xpm_file_to_image(data->connection,
			data->tex_west_path, &data->tex_west.width, &data->tex_west.height);
}

int	wall_text(t_data *data)
{
	load_text(data);
	if (!data->tex_north.img || !data->tex_south.img || !data->tex_east.img
		|| !data->tex_west.img)
		return (printf("Erreur : impossible de charger wall.xpm\n"),
			free_data(data), (1));
	data->tex_north.addr = mlx_get_data_addr(data->tex_north.img,
			&data->tex_north.bpp, &data->tex_north.line_length,
			&data->tex_north.endian);
	data->tex_south.addr = mlx_get_data_addr(data->tex_south.img,
			&data->tex_south.bpp, &data->tex_south.line_length,
			&data->tex_south.endian);
	data->tex_east.addr = mlx_get_data_addr(data->tex_east.img,
			&data->tex_east.bpp, &data->tex_east.line_length,
			&data->tex_east.endian);
	data->tex_west.addr = mlx_get_data_addr(data->tex_west.img,
			&data->tex_west.bpp, &data->tex_west.line_length,
			&data->tex_west.endian);
	if (!data->tex_north.img || !data->tex_south.img || !data->tex_east.img
		|| !data->tex_west.img)
		return (printf("Erreur : mlx_get_data_addr a echoue\n"),
			free_data(data), (1));
	return (0);
}

int	check_map(char **argv, t_data *data, t_map_line *current)
{
	int	i;

	if (sec_check(argv, data) == 1)
		return (1);
	i = 0;
	data->map = malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->map)
		return (free_data(data), perror("malloc data->map"), 1);
	current = data->map_data.head;
	while (current)
	{
		data->map[i] = ft_strdup(current->line);
		if (!data->map[i])
		{
			while (i-- > 0)
				free(data->map[i]);
			free(data->map);
			free_data(data);
			return (perror("ft_strdup"), 1);
		}
		current = current->next;
		i++;
	}
	data->map[i] = NULL;
	return (0);
}

int	check_text(t_data *data)
{
	if (!data->connection)
		return (1);
	data->window = mlx_new_window(data->connection, 1024, 512, "Cub3d");
	if (!data->window)
		return (1);
	if (!file_exists("north.xpm") || !file_exists("south.xpm")
		|| !file_exists("east.xpm") || !file_exists("west.xpm"))
	{
		printf("Erreur: fichiers .xpm manquants\n");
		free_data(data);
		return (1);
	}
	if (wall_text(data) == 1)
		return (1);
	data->img.img = mlx_new_image(data->connection, 1024, 512);
	if (!data->img.img)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_map_line	*current;

	current = NULL;
	if (first_check(argc, argv) == 1)
		return (1);
	ft_memset(&data, 0, sizeof(t_data));
	if (check_map(argv, &data, current) == 1)
		return (1);
	starter(&data.player, &data.map_data);
	data.connection = mlx_init();
	if (check_text(&data) == 1)
		return (1);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bpp,
			&data.img.line_length, &data.img.endian);
	mlx_hook(data.window, 2, 1L << 0, handle_key_press, &data);
	mlx_hook(data.window, 3, 1L << 1, handle_key_release, &data);
	mlx_loop_hook(data.connection, render_frame, &data);
	mlx_hook(data.window, 17, 0, close_window, &data);
	mlx_loop(data.connection);
	return (0);
}
