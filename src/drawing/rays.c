/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:32:12 by hkaddour          #+#    #+#             */
/*   Updated: 2023/02/16 21:35:24 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

//not using it no more
int	ray_sight(t_data *data)
{
	if (data->ray->ray_angle >= 0 && data->ray->ray_angle <= M_PI)
		return (1);
	return (0);
}

void	get_first_horizontal_intersect(t_data *data, double angle)
{
	data->draw_utils->x = data->draw_utils->ply_x_pos;
	data->draw_utils->y = data->draw_utils->ply_y_pos;
	if ((int)convert_rad2deg(angle) >= 180 && \
			(int)convert_rad2deg(angle) <= 360)
		data->ray->y_horizontal = floor(data->draw_utils->y / SQR_SIZE) * SQR_SIZE;
	else if ((int)convert_rad2deg(angle) >= 0 \
			&& (int)convert_rad2deg(angle) < 180)
		data->ray->y_horizontal = floor(data->draw_utils->y / SQR_SIZE) * SQR_SIZE + SQR_SIZE;
	data->ray->x_horizontal = data->draw_utils->x + \
		(data->ray->y_horizontal - data->draw_utils->y) / tan(angle);
}

void	get_next_horizontal_intersect(t_data *data, double angle)
{
	if (((int)convert_rad2deg(angle) >= 180 && \
			(int)convert_rad2deg(angle) <= 360))
	{
		data->ray->y_horizontal -= SQR_SIZE;
		data->ray->x_horizontal += (-SQR_SIZE / tan(angle));
	}
	else if ((int)convert_rad2deg(angle) >= 0 \
			&& (int)convert_rad2deg(angle) < 180)
	{
		data->ray->y_horizontal += SQR_SIZE;
		data->ray->x_horizontal += (SQR_SIZE / tan(angle));
	}
}

void	get_first_vertical_intersect(t_data *data, double angle)
{
	data->draw_utils->x = data->draw_utils->ply_x_pos;
	data->draw_utils->y = data->draw_utils->ply_y_pos;
	if (((int)convert_rad2deg(angle) >= 270 && (int)convert_rad2deg(angle) <= 360) || \
			((int)convert_rad2deg(angle) >= 0 && (int)convert_rad2deg(angle) <= 90))
		data->ray->x_vertical = floor(data->draw_utils->x / SQR_SIZE) * SQR_SIZE + SQR_SIZE;
	else if ((int)convert_rad2deg(angle) > 90 \
			&& (int)convert_rad2deg(angle) < 270)
		data->ray->x_vertical = floor(data->draw_utils->x / SQR_SIZE) * SQR_SIZE;
	data->ray->y_vertical = data->draw_utils->y + \
		(data->ray->x_vertical - data->draw_utils->x) * tan(angle);
}

void	get_next_vertical_intersect(t_data *data, double angle)
{
	if (((int)convert_rad2deg(angle) >= 270 && (int)convert_rad2deg(angle) <= 360) || \
			((int)convert_rad2deg(angle) >= 0 && (int)convert_rad2deg(angle) <= 90))
	{
		data->ray->x_vertical += SQR_SIZE;
		data->ray->y_vertical += (SQR_SIZE * tan(angle));
	}
	else if ((int)convert_rad2deg(angle) > 90 \
			&& (int)convert_rad2deg(angle) < 270)
	{
		data->ray->x_vertical -= SQR_SIZE;
		data->ray->y_vertical += (-SQR_SIZE * tan(angle));
	}
}

void	get_horizontal_intersect(t_data *data, double angle)
{
	if ((int)convert_rad2deg(angle) != 0 \
			&& (int)convert_rad2deg(angle) != 180)
	{
		get_first_horizontal_intersect(data, angle);
		if (data->ray->x_horizontal < 0 || data->ray->x_horizontal > data->map->width * SQR_SIZE \
				|| data->ray->y_horizontal < 0 || data->ray->y_horizontal > data->map->height * SQR_SIZE)
		{
			data->ray->chk_if_horz = 1;
			return ;
		}
		if (did_it_hit_the_wall(data, data->ray->x_horizontal, data->ray->y_horizontal + round(SQR_SIZE / 10)) && \
				did_it_hit_the_wall(data, data->ray->x_horizontal, data->ray->y_horizontal - round(SQR_SIZE / 10)))
		{
			while (1)
			{
				get_next_horizontal_intersect(data, angle);
				if (data->ray->x_horizontal < 0 || data->ray->x_horizontal > data->map->width * SQR_SIZE \
						|| data->ray->y_horizontal < 0 || data->ray->y_horizontal > data->map->height * SQR_SIZE)
				{
					data->ray->chk_if_horz = 1;
					break ;
				}
				if (!did_it_hit_the_wall(data, data->ray->x_horizontal, data->ray->y_horizontal + round(SQR_SIZE / 10)) || \
						!did_it_hit_the_wall(data, data->ray->x_horizontal, data->ray->y_horizontal - round(SQR_SIZE / 10)))
					break ;
			}
		}
	}
	else
		data->ray->chk_if_horz = 1;
}

void	get_vertical_intersect(t_data *data, double angle)
{
	if ((int)convert_rad2deg(angle) != 270 \
			&& (int)convert_rad2deg(angle) != 90)
	{
		get_first_vertical_intersect(data, angle);
		//take this off of change it
		if (data->ray->x_vertical < 0 || data->ray->x_vertical > data->map->width * SQR_SIZE \
				|| data->ray->y_vertical < 0 || data->ray->y_vertical > data->map->height * SQR_SIZE)
		{
			data->ray->chk_if_vert = 1;
			return ;
		}
		if (did_it_hit_the_wall(data, data->ray->x_vertical + round(SQR_SIZE / 10), data->ray->y_vertical) && \
				did_it_hit_the_wall(data, data->ray->x_vertical - round(SQR_SIZE / 10), data->ray->y_vertical))
		{
			while (1)
			{
				get_next_vertical_intersect(data, angle);
				//take this off of change it
				if (data->ray->x_vertical < 0 || data->ray->x_vertical > data->map->width * SQR_SIZE \
						|| data->ray->y_vertical < 0 || data->ray->y_vertical > data->map->height * SQR_SIZE)
				{
					data->ray->chk_if_vert = 1;
					break ;
				}
				if (!did_it_hit_the_wall(data, data->ray->x_vertical + round(SQR_SIZE / 10), data->ray->y_vertical) || \
						!did_it_hit_the_wall(data, data->ray->x_vertical - round(SQR_SIZE / 10), data->ray->y_vertical))
					break ;
			}
		}
	}
	else
		data->ray->chk_if_vert = 1;
}

void	compare_the_intersects(t_data *data)
{
	double x;
	double y;

	if (data->ray->chk_if_horz)
	{
		//for vertical
		data->draw_utils->x_next = data->ray->x_vertical;
		data->draw_utils->y_next = data->ray->y_vertical;
	}
	else if (data->ray->chk_if_vert)
	{
		//for horizontal
		data->draw_utils->x_next = data->ray->x_horizontal;
		data->draw_utils->y_next = data->ray->y_horizontal;
	}
	else
	{
		x = fabs(data->draw_utils->x - data->ray->x_horizontal);
		y = fabs(data->draw_utils->y - data->ray->y_horizontal);
		data->ray->dist_horz = sqrt((x * x) + (y * y));
		x = fabs(data->draw_utils->x - data->ray->x_vertical);
		y = fabs(data->draw_utils->y - data->ray->y_vertical);
		data->ray->dist_vert = sqrt((x * x) + (y * y));
		if ((int)round(data->ray->dist_horz) < (int)round(data->ray->dist_vert))
		{
			data->draw_utils->x_next = data->ray->x_horizontal;
			data->draw_utils->y_next = data->ray->y_horizontal;
		}
		else
		{
			data->draw_utils->x_next = data->ray->x_vertical;
			data->draw_utils->y_next = data->ray->y_vertical;
		}
	}
}

void	draw_rays(t_data *data)
{
	int	i;
	double	angle;
	double	angle_increment;

	//this one draws the player ray FOV
	//data->draw_utils->x = data->draw_utils->ply_x_pos;
	//data->draw_utils->y = data->draw_utils->ply_y_pos;
	//data->draw_utils->x_next = data->draw_utils->x + cos(data->draw_utils->angle) * 50;
	//data->draw_utils->y_next = data->draw_utils->y + sin(data->draw_utils->angle) * 50;
	//dda(data, 0x00ff00);
	i = 0;
	angle = data->ray->ray_angle;
	angle_increment = convert_deg2rad(FOV) / WIN_W;
	//this draw all the rays
	while (i <= WIN_W)
	{
		data->ray->chk_if_horz = 0;
		data->ray->chk_if_vert = 0;
		get_horizontal_intersect(data, angle);
		get_vertical_intersect(data, angle);
		compare_the_intersects(data);
		dda(data, 0xff0000);
		if ((int)convert_rad2deg(angle) == 360)
			angle = 0;
		//this calcul should save in a variable
		//angle += convert_deg2rad(FOV) / WIN_W;
		angle += angle_increment;
		i++;
	}
}
