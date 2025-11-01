/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:26:15 by sachanai          #+#    #+#             */
/*   Updated: 2025/10/21 14:56:47 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*skip_whitespace(const char *str)
{
	if (!str)
		return (NULL);
	while (ft_iswhitespace(*str))
	{
		str++;
	}
	return ((char *)str);
}

int	is_only_spaces(char *line)
{
	if (!line)
		return (1);
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n' && *line != '\r')
			return (0);
		line++;
	}
	return (1);
}

int	is_empty_or_comment(const char *line)
{
	if (!line)
		return (SUCCESS);
	if (is_only_spaces((char *)line))
		return (SUCCESS);
	if (line[0] == '#')
		return (SUCCESS);
	if (line[0] == '\0')
		return (SUCCESS);
	return (ERROR);
}

//trouver les premieres et dernieres lignes valides = non vides de la map
int	find_valid_lines(t_map_data *map, int *first, int *last)
{
	t_map_line	*cur;
	int			i;

	*first = -1;
	*last = -1;
	i = 0;
	cur = map->head;
	while (cur)
	{
		if (!is_only_spaces(cur->line))
		{
			if (*first == -1)
				*first = i;
			*last = i;
		}
		cur = cur->next;
		i++;
	}
	if (*first == -1 || *last == -1)
		return (printf("Map error: Map is empty.\n"), 0);
	return (1);
}

//verifier qu'il n'y a pas de lignes vides au milieu de la map
int	check_map_no_empty_lines_in_middle(t_map_data *map)
{
	t_map_line	*cur;
	int			first;
	int			last;
	int			i;

	first = -1;
	last = -1;
	i = 0;
	cur = map->head;
	if (!find_valid_lines(map, &first, &last))
		return (0);
	cur = map->head;
	i = 0;
	while (cur && i <= last)
	{
		if (i >= first && is_only_spaces(cur->line))
			return (printf("Map error: Empty/space line in map.\n"), 0);
		cur = cur->next;
		i++;
	}
	return (1);
}
