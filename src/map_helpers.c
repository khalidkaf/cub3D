/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:47:43 by sachanai          #+#    #+#             */
/*   Updated: 2025/11/01 14:09:18 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// recupere la ligne y de la map
t_map_line	*get_map_line_at(t_map_data *map, int y)
{
	t_map_line	*cur;
	int			i;

	cur = map->head;
	i = 0;
	while (cur)
	{
		if (i == y)
			return (cur);
		cur = cur->next;
		i++;
	}
	return (NULL);
}

// recupere le char a la position (colonne x, ligne y) de la map
char	get_map_at_index(t_map_data *map_data, int x, int y)
{
	t_map_line	*cur;
	int			i;
	int			len;

	if (x < 0 || y < 0)
		return (' ');
	cur = map_data->head;
	if (!cur && !cur->line)
		return (' ');
	i = 0;
	while (cur && i < y)
	{
		cur = cur->next;
		i++;
	}
	len = ft_strlen(cur->line);
	if (x >= len)
		return (' ');
	return (cur->line[x]);
}

// verif si une case touche un espace ou l'exterieur de la map)
int	has_bad_neighbor(t_map_data *map, int x, int y)
{
	char	up;
	char	down;
	char	left;
	char	right;

	up = get_map_at_index(map, x, y - 1);
	down = get_map_at_index(map, x, y + 1);
	left = get_map_at_index(map, x - 1, y);
	right = get_map_at_index(map, x + 1, y);
	if (up == ' ')
		return (1);
	if (down == ' ')
		return (1);
	if (left == ' ')
		return (1);
	if (right == ' ')
		return (1);
	return (0);
}

// calcule nb ttl de lignes de la map
int	get_map_height(t_map_data *map_data)
{
	t_map_line	*cur;
	int			h;

	cur = map_data->head;
	h = 0;
	while (cur)
	{
		h++;
		cur = cur->next;
	}
	return (h);
}

// trouve la ligne la + longue de la map
int	get_map_width(t_map_data *map_data)
{
	t_map_line	*cur;
	int			max;
	int			len;

	cur = map_data->head;
	max = 0;
	while (cur)
	{
		len = ft_strlen(cur->line);
		if (len > max)
			max = len;
		cur = cur->next;
	}
	return (max);
}
