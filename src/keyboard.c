/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:35:52 by kkafmagh          #+#    #+#             */
/*   Updated: 2025/11/02 18:35:53 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_key_press(int keycode, t_data *data)
{
	if (keycode == XK_w)
		data->keys.up = 1;
	if (keycode == XK_s)
		data->keys.down = 1;
	if (keycode == XK_a)
		data->keys.left = 1;
	if (keycode == XK_d)
		data->keys.right = 1;
	if (keycode == XK_Left)
		data->keys.rotate_left = 1;
	if (keycode == XK_Right)
		data->keys.rotate_right = 1;
	if (keycode == XK_Escape)
	{
		free_data(data);
		exit(0);
	}
	return (0);
}

int	handle_key_release(int keycode, t_data *data)
{
	if (keycode == XK_w)
		data->keys.up = 0;
	if (keycode == XK_s)
		data->keys.down = 0;
	if (keycode == XK_a)
		data->keys.left = 0;
	if (keycode == XK_d)
		data->keys.right = 0;
	if (keycode == XK_Left)
		data->keys.rotate_left = 0;
	if (keycode == XK_Right)
		data->keys.rotate_right = 0;
	return (0);
}

int	close_window(t_data *data)
{
	free_data(data);
	exit(0);
	return (0);
}
