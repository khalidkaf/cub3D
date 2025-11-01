/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_id.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 08:25:17 by sarah             #+#    #+#             */
/*   Updated: 2025/11/01 12:17:05 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	process_single_identifier_line(t_data *data, int fd, int *count)
{
	char	*line;
	char	*clean_line;

	line = get_next_line(fd);
	if (!line)
		return (ERROR);
	clean_line = skip_whitespace(line);
	if (!is_empty_or_comment(clean_line))
	{
		if (process_identifier_line(data, clean_line) == SUCCESS)
			(*count)++;
		else
		{
			printf("Error: Invalid identifier\n");
			free(line);
			return (ERROR);
		}
	}
	free(line);
	return (SUCCESS);
}

int	collect_identifiers(t_data *data, int fd)
{
	int	count;
	int	ret;

	count = 0;
	ret = 0;
	while (count < 6)
	{
		ret = process_single_identifier_line(data, fd, &count);
		if (ret == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

int	process_identifier_line(t_data *data, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "N ", 2) == 0
		|| ft_strncmp(line, "SO ", 3) == 0 || ft_strncmp(line, "S ", 2) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "W ", 2) == 0
		|| ft_strncmp(line, "EA ", 3) == 0 || ft_strncmp(line, "E ", 2) == 0)
		return (parse_texture_line(data, line));
	if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "FL ", 3) == 0
		|| ft_strncmp(line, "C ", 2) == 0 || ft_strncmp(line, "CE ", 3) == 0)
		return (parse_color_line(data, line));
	return (ERROR);
}
