/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:05:43 by sachanai          #+#    #+#             */
/*   Updated: 2025/11/01 12:15:34 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map_line(t_map_line *cur, t_map_line *next)
{
	while (cur)
	{
		next = cur->next;
		if (cur->line)
			free(cur->line);
		free(cur);
		cur = next;
	}
}

void	free_path(t_data *data, t_map_line *cur, t_map_line *next)
{
	if (data->tex_north_path)
		free(data->tex_north_path);
	if (data->tex_south_path)
		free(data->tex_south_path);
	if (data->tex_west_path)
		free(data->tex_west_path);
	if (data->tex_east_path)
		free(data->tex_east_path);
	if (data->tex_north.img)
		mlx_destroy_image(data->connection, data->tex_north.img);
	if (data->tex_south.img)
		mlx_destroy_image(data->connection, data->tex_south.img);
	if (data->tex_east.img)
		mlx_destroy_image(data->connection, data->tex_east.img);
	if (data->tex_west.img)
		mlx_destroy_image(data->connection, data->tex_west.img);
	cur = data->map_data.head;
	mlx_destroy_image(data->connection, data->img.img);
	free_map_line(cur, next);
}

void	free_data(t_data *data)
{
	int			i;
	t_map_line	*cur;
	t_map_line	*next;

	cur = NULL;
	next = NULL;
	i = 0;
	free_path(data, cur, next);
	data->map_data.head = NULL;
	data->map_data.tail = NULL;
	while (data->map[i])
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
	mlx_clear_window(data->connection, data->window);
	mlx_destroy_window(data->connection, data->window);
	mlx_destroy_display(data->connection);
	free(data->connection);
}
