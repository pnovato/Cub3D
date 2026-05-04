/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 06:07:58 by kali              #+#    #+#             */
/*   Updated: 2026/05/04 06:30:59 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_ray(t_data *data, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIDTH - 1;
	data->ray.dir_ray.x = data->player.dir.x + data->player.plane.x * camera_x;
	data->ray.dir_ray.y = data->player.dir.y + data->player.plane.y * camera_x;
	data->ray.map_x = (int)data->player.pos.x;
	data->ray.map_y = (int)data->player.pos.y;
	if (data->ray.dir_ray.x == 0)
		data->ray.delt_x = 1e30;
	else
		data->ray.delt_x = fabs(1 / data->ray.dir_ray.x);
	if (data->ray.dir_ray.y == 0)
		data->ray.delt_y = 1e30;
	else
		data->ray.delt_y = fabs(1 / data->ray.dir_ray.y);
}

void	calc_step(t_data *data)
{
	double	px;
	double	py;

	px = data->player.pos.x;
	py = data->player.pos.y;
	if (data->ray.dir_ray.x < 0)
	{
		data->ray.step_x = -1;
		data->ray.side_dist_x = (px - data->ray.map_x) * data->ray.delt_x;
	}
	else
	{
		data->ray.step_x = 1;
		data->ray.side_dist_x = (data->ray.map_x + 1.0 - px) * data->ray.delt_x;
	}
	if (data->ray.dir_ray.y < 0)
	{
		data->ray.step_y = -1;
		data->ray.side_dist_y = (py - data->ray.map_y) * data->ray.delt_y;
	}
	else
	{
		data->ray.step_y = 1;
		data->ray.side_dist_y = (data->ray.map_y + 1.0 - py) * data->ray.delt_y;
	}
}

void	perform_dda(t_data *data)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (data->ray.side_dist_x < data->ray.side_dist_y)
		{
			data->ray.side_dist_x += data->ray.delt_x;
			data->ray.map_x += data->ray.step_x;
			data->ray.side_hit = 0;
		}
		else
		{
			data->ray.side_dist_y += data->ray.delt_y;
			data->ray.map_y += data->ray.step_y;
			data->ray.side_hit = 1;
		}
		if (data->map.map[data->ray.map_y][data->ray.map_x] == '1')
			hit = 1;
	}
}
