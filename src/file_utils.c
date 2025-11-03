/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachanai <sachanai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:45:19 by sachanai          #+#    #+#             */
/*   Updated: 2025/09/15 14:12:54 by sachanai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	extension_check(const char *filename)
{
	int	len;

	if (!filename)
	{
		printf("Error: file's name is missing\n");
		return (ERROR);
	}
	len = 0;
	while (filename[len])
		len++;
	if (len < MIN_FILENAME_LEN)
	{
		printf("Error: name's file too short\n");
		return (ERROR);
	}
	if (ft_strcmp(filename + len - 4, CUB_EXTENSION) == 0)
		return (SUCCESS);
	printf("Error: Invalid extension (expected: .cub)\n");
	return (ERROR);
}

int	has_xpm_extension(char *path)
{
	int	len;
	int	i;

	if (!path)
		return (0);
	len = ft_strlen(path);
	i = len - 1;
	while (i >= 0 && (path[i] == '\n' || path[i] == '\r' || path[i] == ' '))
		i--;
	if (i < 3)
		return (0);
	return (path[i - 3] == '.' && path[i - 2] == 'x' && path[i - 1] == 'p'
		&& path[i] == 'm');
}

int	open_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (-1);
	}
	return (fd);
}

int	is_in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	file_exists(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}
