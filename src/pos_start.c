/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:36:27 by kkafmagh          #+#    #+#             */
/*   Updated: 2025/11/02 18:36:28 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pos_start_n(t_player *player, int i, int j)
{
	player->pos_y = i + 0.5;
	player->pos_x = j + 0.5;
	player->dir_x = 0;
	player->dir_y = -1;
	player->plane_x = 0.66;
	player->plane_y = 0;
}

void	pos_start_s(t_player *player, int i, int j)
{
	player->pos_y = i + 0.5;
	player->pos_x = j + 0.5;
	player->dir_x = 0;
	player->dir_y = 1;
	player->plane_x = -0.66;
	player->plane_y = 0;
}

void	pos_start_e(t_player *player, int i, int j)
{
	player->pos_y = i + 0.5;
	player->pos_x = j + 0.5;
	player->dir_x = 1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.66;
}

void	pos_start_w(t_player *player, int i, int j)
{
	player->pos_y = i + 0.5;
	player->pos_x = j + 0.5;
	player->dir_x = -1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = -0.66;
}

void	starter(t_player *player, t_map_data *map)
{
	int			i;
	int			j;
	t_map_line	*current;

	current = map->head;
	i = 0;
	j = 0;
	while (current)
	{
		while (current->line[j])
		{
			if (current->line[j] == 'N')
				return (pos_start_n(player, i, j));
			else if (current->line[j] == 'S')
				return (pos_start_s(player, i, j));
			else if (current->line[j] == 'E')
				return (pos_start_e(player, i, j));
			else if (current->line[j] == 'W')
				return (pos_start_w(player, i, j));
			j++;
		}
		j = 0;
		i++;
		current = current->next;
	}
}
