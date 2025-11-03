/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:06:36 by sachanai          #+#    #+#             */
/*   Updated: 2025/11/03 12:12:01 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_textures(t_data *data)
{
	if (data->tex_north.addr)
		printf("North: %s\n", data->tex_north.addr);
	else
		printf("North: (none)\n");
	if (data->tex_south.addr)
		printf("South: %s\n", data->tex_south.addr);
	else
		printf("South: (none)\n");
	if (data->tex_west.addr)
		printf("West: %s\n", data->tex_west.addr);
	else
		printf("West: (none)\n");
	if (data->tex_east.addr)
		printf("East: %s\n", data->tex_east.addr);
	else
		printf("East: (none)\n");
}

void	print_colors(t_data *data)
{
	printf("Floor color: R=%d   G=%d   B=%d\n", data->floor_color.r,
		data->floor_color.g, data->floor_color.b);
	printf("Ceiling color: R=%d   G=%d   B=%d\n", data->ceiling_color.r,
		data->ceiling_color.g, data->ceiling_color.b);
}

void	print_map(t_data *data)
{
	t_map_line	*cur;

	printf("Map dimensions: width = %d, height = %d\n", data->map_width,
		data->map_height);
	printf("Map:\n");
	cur = data->map_data.head;
	while (cur)
	{
		printf("%s\n", cur->line);
		cur = cur->next;
	}
}

int	error_and_debug(const char *msg, int x, int y, char c)
{
	(void)y;
	(void)c;
	(void)x;
	return (print_map_error(msg));
}
