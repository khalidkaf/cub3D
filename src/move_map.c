/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:36:09 by kkafmagh          #+#    #+#             */
/*   Updated: 2025/11/02 18:36:10 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move1(t_dist *dist, t_data *data)
{
	dist->camera_x = 2 * dist->x / (double)1024 - 1;
	dist->ray_dir_x = data->player.dir_x + data->player.plane_x
		* dist->camera_x;
	dist->ray_dir_y = data->player.dir_y + data->player.plane_y
		* dist->camera_x;
	dist->map_x = (int)data->player.pos_x;
	dist->map_y = (int)data->player.pos_y;
	if (dist->ray_dir_x == 0)
		dist->delta_dist_x = 1e30;
	else
		dist->delta_dist_x = fabs(1 / dist->ray_dir_x);
	if (dist->ray_dir_y == 0)
		dist->delta_dist_y = 1e30;
	else
		dist->delta_dist_y = fabs(1 / dist->ray_dir_y);
}

void	move2(t_dist *dist, t_data *data)
{
	if (dist->ray_dir_x < 0)
	{
		dist->step_x = -1;
		dist->side_dist_x = (data->player.pos_x - dist->map_x)
			* dist->delta_dist_x;
	}
	else
	{
		dist->step_x = 1;
		dist->side_dist_x = (dist->map_x + 1.0 - data->player.pos_x)
			* dist->delta_dist_x;
	}
	if (dist->ray_dir_y < 0)
	{
		dist->step_y = -1;
		dist->side_dist_y = (data->player.pos_y - dist->map_y)
			* dist->delta_dist_y;
	}
	else
	{
		dist->step_y = 1;
		dist->side_dist_y = (dist->map_y + 1.0 - data->player.pos_y)
			* dist->delta_dist_y;
	}
}

void	move_map(t_dist *dist, t_data *data)
{
	move1(dist, data);
	move2(dist, data);
}
