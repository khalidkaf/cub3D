/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 08:11:33 by sachanai          #+#    #+#             */
/*   Updated: 2025/11/01 14:12:06 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_rgb_value(const char *str)
{
	int	value;

	if (!ft_isdigit(*str))
		return (ERROR);
	value = ft_atoi(str);
	if (value < RGB_MIN || value > RGB_MAX)
		return (ERROR);
	return (SUCCESS);
}

// 3nbs separes pr virgule
int	is_valid_color_format(const char *line)
{
	char	*str;
	int		count;

	if (!line)
		return (ERROR);
	str = skip_whitespace(line + 2);
	count = 0;
	while (*str && count < 3)
	{
		str = skip_whitespace(str);
		if (is_valid_rgb_value(str) == ERROR)
			return (ERROR);
		while (*str && ft_isdigit(*str))
			str++;
		str = skip_whitespace(str);
		if (count++ < 2)
		{
			if (*str != ',')
				return (ERROR);
			str = skip_whitespace(str + 1);
		}
	}
	if (count != 3 || *str != '\0')
		return (ERROR);
	return (SUCCESS);
}

// verif doublon id + format
int	check_color_input(t_data *data, char *line)
{
	if (!line || !data)
		return (ERROR);
	if (line[0] == 'F' && data->floor_color.r != -1)
	{
		printf("Error: Duplicate F identifier\n");
		return (ERROR);
	}
	else if (line[0] == 'C' && data->ceiling_color.r != -1)
	{
		printf("Error: Duplicate C identifier\n");
		return (ERROR);
	}
	if (is_valid_color_format(line) == ERROR)
	{
		printf("Error: Invalid color format: %s\n", line);
		return (ERROR);
	}
	return (SUCCESS);
}

int	assign_color_values(t_data *data, char identifier, t_color color)
{
	if (identifier == 'F')
	{
		data->floor_color.r = color.r;
		data->floor_color.g = color.g;
		data->floor_color.b = color.b;
	}
	else if (identifier == 'C')
	{
		data->ceiling_color.r = color.r;
		data->ceiling_color.g = color.g;
		data->ceiling_color.b = color.b;
	}
	else
		return (ERROR);
	return (SUCCESS);
}

int	parse_color_line(t_data *data, char *line)
{
	char	*str;
	t_color	color;

	if (check_color_input(data, line) == ERROR)
		return (ERROR);
	str = skip_whitespace(line + 2);
	color.r = ft_atoi(str);
	while (*str && !(*str == ',' || ft_iswhitespace(*str)))
		str++;
	str = skip_whitespace(str);
	if (*str == ',')
		str++;
	str = skip_whitespace(str);
	color.g = ft_atoi(str);
	while (*str && !(*str == ',' || ft_iswhitespace(*str)))
		str++;
	str = skip_whitespace(str);
	if (*str == ',')
		str++;
	str = skip_whitespace(str);
	color.b = ft_atoi(str);
	if (assign_color_values(data, line[0], color) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
