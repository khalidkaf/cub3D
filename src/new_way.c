/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_way.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:09:02 by sachanai          #+#    #+#             */
/*   Updated: 2025/10/29 19:07:45 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	new_parse_file(t_data *data, const char *filename)
{
	int	fd;

	fd = open_file(filename);
	if (fd == -1)
		return (ERROR);
	if (collect_identifiers(data, fd) == ERROR)
	{
		close (fd);
		return (ERROR);
	}
	if (collect_map_lines(&data->map_data, fd) == ERROR)
	{
		close (fd);
		return (ERROR);
	}
	if (validate_map(data) == ERROR)
	{
		close (fd);
		return (ERROR);
	}
	close(fd);
	return (SUCCESS);
}
