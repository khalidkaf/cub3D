/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 08:35:34 by sarah             #+#    #+#             */
/*   Updated: 2025/11/01 12:01:12 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_data(t_data *data)
{
	if (!data)
		return (ERROR);
	data->tex_north.addr = NULL;
	data->tex_south.addr = NULL;
	data->tex_west.addr = NULL;
	data->tex_east.addr = NULL;
	data->tex_north_path = NULL;
	data->tex_south_path = NULL;
	data->tex_west_path = NULL;
	data->tex_east_path = NULL;
	data->floor_color.r = -1;
	data->floor_color.g = -1;
	data->floor_color.b = -1;
	data->ceiling_color.r = -1;
	data->ceiling_color.g = -1;
	data->ceiling_color.b = -1;
	data->player.pos_x = -1;
	data->player.pos_y = -1;
	data->map_data.head = NULL;
	data->map_data.tail = NULL;
	data->map_width = 0;
	data->map_height = 0;
	return (SUCCESS);
}
