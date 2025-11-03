/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 19:32:43 by sarah             #+#    #+#             */
/*   Updated: 2025/11/02 11:43:47 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//verif si le joueur est a une position valide
static int	handle_player(t_map_data *map, t_cell_info *info, t_data *data)
{
	if (has_bad_neighbor(map, info->x, info->y))
		return (error_and_debug("Player at invalid position"
				"(touches space or outside).", info->x, info->y, info->c));
	if (is_border(info->x, info->y, data->map_width, data->map_height))
		return (error_and_debug("Player on map border.",
				info->x, info->y, info->c));
	return (1);
}

//verif si un espace ouvert est a une position valide
static int	handle_open_space(t_map_data *map, t_cell_info *info, t_data *data)
{
	if (has_bad_neighbor(map, info->x, info->y))
		return (error_and_debug("Open space at invalid position \
			(touches space or outside).", info->x, info->y, info->c));
	if (is_border(info->x, info->y, data->map_width, data->map_height))
		return (error_and_debug("Open space on map border.",
				info->x, info->y, info->c));
	return (1);
}

//verif contenu + validite d'1 case de la map
static int	check_cell(t_map_data *map, t_cell_info *info,
				t_data *data, int *player_count)
{
	info->c = get_map_at_index(map, info->x, info->y);
	if (info->c == -1)
		return (1);
	if (!is_valid_map_char(info->c))
	{
		printf(" INVALID: y=%d x=%d char='%c' ascii=%d\n",
			info->y, info->x, info->c, (unsigned char)info->c);
		return (print_map_error("Invalid character in map."));
	}
	if (is_player(info->c))
	{
		(*player_count)++;
		if (!handle_player(map, info, data))
			return (0);
	}
	if (info->c == '0')
	{
		if (!handle_open_space(map, info, data))
			return (0);
	}
	return (1);
}

//validation globale de la map
int	validate_map(t_data *data)
{
	t_cell_info	info;
	int			player_count;

	if (!check_map_no_empty_lines_in_middle(&data->map_data))
		return (0);
	data->map_height = get_map_height(&data->map_data);
	data->map_width = get_map_width(&data->map_data);
	player_count = 0;
	info.y = 0;
	while (info.y < data->map_height)
	{
		info.x = 0;
		while (info.x < data->map_width)
		{
			if (!check_cell(&data->map_data, &info, data, &player_count))
				return (0);
			info.x++;
		}
		info.y++;
	}
	if (player_count != 1)
		return (print_map_error("There must be exactly"
				" one player on the map."));
	return (1);
}
