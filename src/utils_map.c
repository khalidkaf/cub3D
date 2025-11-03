/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 12:06:45 by sachanai          #+#    #+#             */
/*   Updated: 2025/11/02 18:36:51 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	print_map_error(const char *msg)
{
	printf("Map error: %s\n", msg);
	return (0);
}

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || is_player(c) || c == ' ' || c == '\n'
		|| c == '\r');
}

int	is_border(int x, int y, int width, int height)
{
	return (x == 0 || y == 0 || x == width - 1 || y == height - 1);
}

int	map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}
