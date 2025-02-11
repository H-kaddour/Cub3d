/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_strokes_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:38:09 by hkaddour          #+#    #+#             */
/*   Updated: 2023/02/26 12:42:33 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	key_press(int key, t_data *data)
{
	if (key == UP)
		data->key_mv->key_up = 1;
	if (key == DOWN)
		data->key_mv->key_down = 1;
	if (key == RIGHT)
		data->key_mv->key_right = 1;
	if (key == LEFT)
		data->key_mv->key_left = 1;
	if (key == ROT_RIGHT)
		data->key_mv->rot_rght = 1;
	if (key == ROT_LEFT)
		data->key_mv->rot_lft = 1;
	if (key == VIEW_UP)
		data->key_mv->view_up = 1;
	if (key == VIEW_DOWN)
		data->key_mv->view_down = 1;
	if (key == ESC)
		close_win(data);
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == UP)
		data->key_mv->key_up = 0;
	if (key == DOWN)
		data->key_mv->key_down = 0;
	if (key == RIGHT)
		data->key_mv->key_right = 0;
	if (key == LEFT)
		data->key_mv->key_left = 0;
	if (key == ROT_RIGHT)
		data->key_mv->rot_rght = 0;
	if (key == ROT_LEFT)
		data->key_mv->rot_lft = 0;
	if (key == VIEW_UP)
		data->key_mv->view_up = 0;
	if (key == VIEW_DOWN)
		data->key_mv->view_down = 0;
	return (0);
}

int	view_up_down_key(t_data *data)
{
	if (data->key_mv->view_up)
	{
		if (!(data->ray->view_up_down <= (WIN_H / 2) + 100))
			return (0);
		else
			data->ray->view_up_down += 5;
	}
	if (data->key_mv->view_down)
	{
		if (!(data->ray->view_up_down >= (WIN_H / 2) - 100))
			return (0);
		else
			data->ray->view_up_down -= 5;
	}
	return (1);
}

void	rotation_key(t_data *data)
{
	if (data->key_mv->rot_rght)
	{
		if ((int)round(convert_rad2deg(data->draw_utils->angle)) == 0)
			data->draw_utils->angle = (2 * M_PI);
		data->draw_utils->angle = \
			fabs(data->draw_utils->angle - convert_deg2rad(ROT_SPEED));
		if ((int)round(convert_rad2deg(data->ray->ray_angle)) == 0)
			data->ray->ray_angle = (2 * M_PI);
		data->ray->ray_angle = \
			fabs(data->ray->ray_angle - convert_deg2rad(ROT_SPEED));
	}
	if (data->key_mv->rot_lft)
	{
		if ((int)round(convert_rad2deg(data->draw_utils->angle)) == 360)
			data->draw_utils->angle = 0;
		data->draw_utils->angle += convert_deg2rad(ROT_SPEED);
		if ((int)round(convert_rad2deg(data->ray->ray_angle)) == 360)
			data->ray->ray_angle = 0;
		data->ray->ray_angle += convert_deg2rad(ROT_SPEED);
	}
}
