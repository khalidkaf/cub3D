/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:36:43 by kkafmagh          #+#    #+#             */
/*   Updated: 2025/11/02 18:36:44 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	edge_tex_y(t_dist *dist, t_data *data, t_texture *tex)
{
	char	*tex_pixel;
	int		color;

	while (dist->y <= dist->draw_end)
	{
		dist->d = dist->y * 256 - 512 * 128 + dist->line_height * 128;
		dist->tex_y = ((dist->d * tex->height) / dist->line_height) / 256;
		if (dist->tex_y < 0)
			dist->tex_y = 0;
		if (dist->tex_y >= tex->height)
			dist->tex_y = tex->height - 1;
		if (dist->tex_y >= 0 && dist->tex_y < tex->height && dist->tex_x >= 0
			&& dist->tex_x < tex->width)
		{
			tex_pixel = tex->addr + (dist->tex_y * tex->line_length
					+ dist->tex_x * (tex->bpp / 8));
			color = *(unsigned int *)tex_pixel;
			my_mlx_pixel_put(&data->img, dist->x, dist->y, color);
		}
		dist->y++;
	}
}

void	coor_x(t_dist *dist, t_data *data, t_texture *tex)
{
	if (dist->side == 0)
		dist->wall_x = data->player.pos_y + dist->perp_wall_dist
			* dist->ray_dir_y;
	else
		dist->wall_x = data->player.pos_x + dist->perp_wall_dist
			* dist->ray_dir_x;
	dist->wall_x -= floor(dist->wall_x);
	dist->tex_x = (int)(dist->wall_x * tex->width);
	if ((dist->side == 0 && dist->ray_dir_x > 0) || (dist->side == 1
			&& dist->ray_dir_y < 0))
		dist->tex_x = tex->width - dist->tex_x - 1;
	if (dist->tex_x < 0)
		dist->tex_x = 0;
	if (dist->tex_x >= tex->width)
		dist->tex_x = tex->width - 1;
	dist->y = dist->draw_start;
	edge_tex_y(dist, data, tex);
}

void	rendering(t_dist *dist, t_data *data, t_texture *tex)
{
	while (dist->x < 1024)
	{
		move_map(dist, data);
		dda(dist, data);
		if (!dist->hit)
		{
			dist->x++;
			continue ;
		}
		chose_text(dist, data, &tex);
		if (!tex || !tex->addr || tex->width <= 0 || tex->height <= 0
			|| tex->line_length <= 0)
		{
			dist->y = dist->draw_start;
			while (dist->y <= dist->draw_end)
			{
				my_mlx_pixel_put(&data->img, dist->x, dist->y, 0xFF00FF);
				dist->y++;
			}
			dist->x++;
			continue ;
		}
		coor_x(dist, data, tex);
		dist->x++;
	}
}

int	render_frame(t_data *param)
{
	t_data		*data;
	t_texture	*tex;
	t_dist		dist_stack;
	t_dist		*dist;

	dist = &dist_stack;
	tex = NULL;
	data = (t_data *)param;
	update_player(data);
	color_floor_ceiling(data);
	dist->x = 0;
	rendering(dist, data, tex);
	mlx_put_image_to_window(data->connection, data->window, data->img.img, 0,
		0);
	return (0);
}
