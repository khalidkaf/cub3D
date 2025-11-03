/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pose_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:36:39 by kkafmagh          #+#    #+#             */
/*   Updated: 2025/11/02 18:39:18 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	color_floor_ceiling(t_data *data)
{
	int	ceiling_color;
	int	floor_color;
	int	y;
	int	x2;

	y = 0;
	x2 = 0;
	ceiling_color = data->ceiling_color.r * 65536 + data->ceiling_color.g * 256
		+ data->ceiling_color.b;
	floor_color = data->floor_color.r * 65536 + data->floor_color.g * 256
		+ data->floor_color.b;
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
}

void	pre_text(t_dist *dist, t_data *data, t_texture **tex)
{
	if (dist->side == 0)
	{
		if (dist->ray_dir_x > 0)
			*tex = &data->tex_west;
		else
			*tex = &data->tex_east;
	}
	else
	{
		if (dist->ray_dir_y > 0)
			*tex = &data->tex_north;
		else
			*tex = &data->tex_south;
	}
}

void	chose_text(t_dist *dist, t_data *data, t_texture **tex)
{
	pre_text(dist, data, tex);
	if (dist->side == 0)
		dist->perp_wall_dist = dist->side_dist_x - dist->delta_dist_x;
	else
		dist->perp_wall_dist = dist->side_dist_y - dist->delta_dist_y;
	dist->line_height = (int)(512 / dist->perp_wall_dist);
	if (dist->line_height == 0)
		dist->line_height = 1;
	dist->draw_start = -dist->line_height / 2 + 512 / 2;
	dist->draw_end = dist->line_height / 2 + 512 / 2;
	if (dist->draw_start < 0)
		dist->draw_start = 0;
	if (dist->draw_end >= 512)
		dist->draw_end = 512 - 1;
}
