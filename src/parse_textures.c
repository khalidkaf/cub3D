/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 08:11:19 by sachanai          #+#    #+#             */
/*   Updated: 2025/11/01 14:42:53 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_texture(char **texture, char *path, const char *id)
{
	if (*texture != NULL)
	{
		printf("Error: Duplicate %s identifier\n", id);
		free(path);
		return (ERROR);
	}
	if (!has_xpm_extension(path))
	{
		printf("Error: Texture file for %s must have a .xpm extension\n", id);
		free(path);
		return (ERROR);
	}
	*texture = path;
	return (SUCCESS);
}

char	*del_backspace(char *line)
{
	int		i;
	int		j;
	char	*newline;

	i = 0;
	j = 0;
	newline = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!newline)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '\n')
			break ;
		newline[j++] = line[i++];
	}
	newline[j] = '\0';
	return (newline);
}

// int	parse_texture_line(t_data *data, char *line)
// {
// 	char	*path;

// 	if (!line || !data)
// 		return (ERROR);
// 	path = del_backspace(skip_whitespace(line + 3));
// 	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "N ", 2) == 0)
// 	{
// 		if (ft_strncmp(line, "NO ", 3) == 0)
// 			return (handle_texture(&data->tex_north.addr, path, "NO"));
// 		else
// 		{
// 			path = del_backspace(skip_whitespace(line + 2));
// 			return (handle_texture(&data->tex_north.addr, path, "NO"));
// 		}
// 	}
// 	// return (handle_texture(&data->tex_north.addr, path, "NO"));
// 	else if (ft_strncmp(line, "SO ", 3) == 0 || ft_strncmp(line, "S ", 2) == 0)
// 		if (ft_strncmp(line, "SO ", 3) == 0)
// 			return (handle_texture(&data->tex_south.addr, path, "SO"));
// 		else
// 		{
// 			path = del_backspace(skip_whitespace(line + 2));
// 			return (handle_texture(&data->tex_south.addr, path, "SO"));
// 		}
// 	// return (handle_texture(&data->tex_south.addr, path, "SO"));
// 	else if (ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "W ", 2) == 0)
// 		if (ft_strncmp(line, "WE ", 3) == 0)
// 			return (handle_texture(&data->tex_west.addr, path, "WE"));
// 		else
// 		{
// 			path = del_backspace(skip_whitespace(line + 2));
// 			return (handle_texture(&data->tex_west.addr, path, "WE"));
// 		}
// 	// return (handle_texture(&data->tex_west.addr, path, "WE"));
// 	else if (ft_strncmp(line, "EA ", 3) == 0 || ft_strncmp(line, "E ", 2) == 0)
// 	if (ft_strncmp(line, "EA ", 3) == 0)
// 			return (handle_texture(&data->tex_east.addr, path, "EA"));
// 		else
// 		{
// 			path = del_backspace(skip_whitespace(line + 2));
// 			return (handle_texture(&data->tex_east.addr, path, "EA"));
// 		}
// 		// return (handle_texture(&data->tex_east.addr, path, "EA"));
// 	else
// 		return (ERROR);
// }

int	set_offset(t_data *data, char *line)
{
	int	offset;

	if (!line || !data)
		return (ERROR);
	if (ft_strncmp(line, "NO ", 3) == 0)
		offset = 3;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		offset = 3;
	else if (ft_strncmp(line, "WE ", 3) == 0)
		offset = 3;
	else if (ft_strncmp(line, "EA ", 3) == 0)
		offset = 3;
	else if (ft_strncmp(line, "N ", 2) == 0)
		offset = 2;
	else if (ft_strncmp(line, "S ", 2) == 0)
		offset = 2;
	else if (ft_strncmp(line, "W ", 2) == 0)
		offset = 2;
	else if (ft_strncmp(line, "E ", 2) == 0)
		offset = 2;
	else
		return (ERROR);
	return (offset);
}

int	end_parse(char **target_path, char *path)
{
	if (*target_path != NULL)
	{
		printf("Error: Duplicate texture identifier\n");
		free(path);
		return (ERROR);
	}
	if (!has_xpm_extension(path))
	{
		printf("Error: Texture must have .xpm extension\n");
		free(path);
		return (ERROR);
	}
	*target_path = path;
	return (1);
}

int	parse_texture_line(t_data *data, char *line)
{
	char	*path;
	int		offset;
	char	**target_path;

	offset = set_offset(data, line);
	if (offset == 0)
		return (ERROR);
	path = del_backspace(skip_whitespace(line + offset));
	if (!path)
		return (ERROR);
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "N ", 2) == 0)
		target_path = &data->tex_north_path;
	else if (ft_strncmp(line, "SO ", 3) == 0 || ft_strncmp(line, "S ", 2) == 0)
		target_path = &data->tex_south_path;
	else if (ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "W ", 2) == 0)
		target_path = &data->tex_west_path;
	else if (ft_strncmp(line, "EA ", 3) == 0 || ft_strncmp(line, "E ", 2) == 0)
		target_path = &data->tex_east_path;
	else
		return (free(path), ERROR);
	if (end_parse(target_path, path) == 0)
		return (ERROR);
	return (SUCCESS);
}
