/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:36:47 by kkafmagh          #+#    #+#             */
/*   Updated: 2025/11/02 18:36:48 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	update_player(t_data *data)
{
	t_player	*p;
	int			new_x;
	int			new_y;

	new_x = 0;
	new_y = 0;
	p = &data->player;
	if (data->keys.up)
		go_up(new_x, new_y, p, data);
	if (data->keys.down)
		go_down(new_x, new_y, p, data);
	if (data->keys.left)
		go_left(new_x, new_y, p, data);
	if (data->keys.right)
		go_right(new_x, new_y, p, data);
	if (data->keys.rotate_left)
		rotate_player(p, -ROT_SPEED);
	if (data->keys.rotate_right)
		rotate_player(p, ROT_SPEED);
}

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (!img || !img->addr)
		return ;
	if (x < 0 || y < 0 || x >= 1024 || y >= 512)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	dda(t_dist *dist, t_data *data)
{
	dist->hit = 0;
	while (!dist->hit)
	{
		if (dist->side_dist_x < dist->side_dist_y)
		{
			dist->side_dist_x += dist->delta_dist_x;
			dist->map_x += dist->step_x;
			dist->side = 0;
		}
		else
		{
			dist->side_dist_y += dist->delta_dist_y;
			dist->map_y += dist->step_y;
			dist->side = 1;
		}
		if (dist->map_y < 0 || dist->map_y >= data->map_height)
			break ;
		if (dist->map_x < 0
			|| dist->map_x >= (int)ft_strlen(data->map[dist->map_y]))
			break ;
		if (data->map[dist->map_y][dist->map_x] == '1')
			dist->hit = 1;
	}
}
