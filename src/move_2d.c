/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:36:03 by kkafmagh          #+#    #+#             */
/*   Updated: 2025/11/02 18:36:04 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	go_up(int new_x, int new_y, t_player *p, t_data *data)
{
	new_x = (int)(p->pos_x + p->dir_x * MOVE_SPEED);
	new_y = (int)(p->pos_y + p->dir_y * MOVE_SPEED);
	if (is_valid_position(data, new_x, (int)p->pos_y))
		p->pos_x += p->dir_x * MOVE_SPEED;
	if (is_valid_position(data, (int)p->pos_x, new_y))
		p->pos_y += p->dir_y * MOVE_SPEED;
}

void	go_down(int new_x, int new_y, t_player *p, t_data *data)
{
	new_x = (int)(p->pos_x - p->dir_x * MOVE_SPEED);
	new_y = (int)(p->pos_y - p->dir_y * MOVE_SPEED);
	if (is_valid_position(data, new_x, (int)p->pos_y))
		p->pos_x -= p->dir_x * MOVE_SPEED;
	if (is_valid_position(data, (int)p->pos_x, new_y))
		p->pos_y -= p->dir_y * MOVE_SPEED;
}

void	go_left(int new_x, int new_y, t_player *p, t_data *data)
{
	new_x = (int)(p->pos_x - p->plane_x * MOVE_SPEED);
	new_y = (int)(p->pos_y - p->plane_y * MOVE_SPEED);
	if (is_valid_position(data, new_x, (int)p->pos_y))
		p->pos_x -= p->plane_x * MOVE_SPEED;
	if (is_valid_position(data, (int)p->pos_x, new_y))
		p->pos_y -= p->plane_y * MOVE_SPEED;
}

void	go_right(int new_x, int new_y, t_player *p, t_data *data)
{
	new_x = (int)(p->pos_x + p->plane_x * MOVE_SPEED);
	new_y = (int)(p->pos_y + p->plane_y * MOVE_SPEED);
	if (is_valid_position(data, new_x, (int)p->pos_y))
		p->pos_x += p->plane_x * MOVE_SPEED;
	if (is_valid_position(data, (int)p->pos_x, new_y))
		p->pos_y += p->plane_y * MOVE_SPEED;
}
