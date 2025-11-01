/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_map_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 10:35:50 by sarah             #+#    #+#             */
/*   Updated: 2025/11/01 12:18:17 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*mise en memoire de la map en utilisant liste chainee pr stock chq ligne lue
-> manip dynamique map taille varibale.
*/

// construc* chq maillon L-C
t_map_line	*create_map_line(char *line_content)
{
	t_map_line	*new_line;
	char		*clean;

	new_line = malloc(sizeof(t_map_line));
	if (!new_line)
		return (NULL);
	clean = ft_strtrim(line_content, "\n");
	if (!clean)
	{
		free(new_line);
		return (NULL);
	}
	new_line->line = ft_strdup(clean);
	free(clean);
	new_line->next = NULL;
	return (new_line);
}

// ajout new element a la fin de la L-C
void	add_map_line(t_map_data *map, t_map_line *new_line)
{
	if (!map->head)
	{
		map->head = new_line;
		map->tail = new_line;
	}
	else
	{
		map->tail->next = new_line;
		map->tail = new_line;
	}
}

// lecture fichier ligne par ligne et stockage dans L-C
int	collect_map_lines(t_map_data *map, int fd)
{
	char		*line;
	t_map_line	*new_node;

	line = get_next_line(fd);
	while (line)
	{
		new_node = create_map_line(line);
		if (!new_node)
		{
			free(line);
			return (ERROR);
		}
		add_map_line(map, new_node);
		free(line);
		line = get_next_line(fd);
	}
	if (!map->head)
		return (ERROR);
	return (SUCCESS);
}
