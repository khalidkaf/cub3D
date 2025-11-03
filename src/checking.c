/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:35:30 by kkafmagh          #+#    #+#             */
/*   Updated: 2025/11/03 10:48:32 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	first_check(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: %s <map_file.cub>\n", argv[0]);
		return (1);
	}
	if (extension_check(argv[1]) == ERROR)
		return (1);
	return (0);
}

int	sec_check(char **argv, t_data *data)
{
	if (init_data(data) == ERROR)
		return (1);
	if (new_parse_file(data, argv[1]) == ERROR)
	{
		printf("Parsing failed.\n");
		get_next_line(-1);
		free_data_sans_map(data);
		return (1);
	}
	if (!data->map_data.head)
	{
		printf("Erreur lors du parsing de la map\n");
		free_data_sans_map(data);
		return (1);
	}
	return (0);
}
