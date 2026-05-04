/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 06:10:04 by kali              #+#    #+#             */
/*   Updated: 2026/05/04 06:23:05 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	move_ws(t_data *data, double s)
{
	double	px;
	double	py;
	double	dx;
	double	dy;

	px = data->player.pos.x;
	py = data->player.pos.y;
	dx = data->player.dir.x * s;
	dy = data->player.dir.y * s;
	if (data->keys.w)
	{
		if (data->map.map[(int)py][(int)(px + dx)] != '1')
			data->player.pos.x += dx;
		if (data->map.map[(int)(py + dy)][(int)px] != '1')
			data->player.pos.y += dy;
	}
	if (data->keys.s)
	{
		if (data->map.map[(int)py][(int)(px - dx)] != '1')
			data->player.pos.x -= dx;
		if (data->map.map[(int)(py - dy)][(int)px] != '1')
			data->player.pos.y -= dy;
	}
}

static void	move_ad(t_data *data, double s)
{
	double	px;
	double	py;
	double	px_s;
	double	py_s;

	px = data->player.pos.x;
	py = data->player.pos.y;
	px_s = data->player.plane.x * s;
	py_s = data->player.plane.y * s;
	if (data->keys.a)
	{
		if (data->map.map[(int)py][(int)(px - px_s)] != '1')
			data->player.pos.x -= px_s;
		if (data->map.map[(int)(py - py_s)][(int)px] != '1')
			data->player.pos.y -= py_s;
	}
	if (data->keys.d)
	{
		if (data->map.map[(int)py][(int)(px + px_s)] != '1')
			data->player.pos.x += px_s;
		if (data->map.map[(int)(py + py_s)][(int)px] != '1')
			data->player.pos.y += py_s;
	}
}

void	move_player(t_data *data)
{
	double	s;
	double	r;

	s = 0.05;
	r = 0.04;
	move_ws(data, s);
	move_ad(data, s);
	if (data->keys.left)
		rotate_player(data, -r);
	if (data->keys.right)
		rotate_player(data, r);
}
