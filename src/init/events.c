/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 12:00:00 by kali              #+#    #+#             */
/*   Updated: 2026/05/04 06:55:18 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	key_press(int keycode, t_data *data)
{
	if (keycode == 65307)
		handle_close(data);
	if (keycode == 119 || keycode == 65362)
		data->keys.w = 1;
	if (keycode == 115 || keycode == 65364)
		data->keys.s = 1;
	if (keycode == 97)
		data->keys.a = 1;
	if (keycode == 100)
		data->keys.d = 1;
	if (keycode == 65361)
		data->keys.left = 1;
	if (keycode == 65363)
		data->keys.right = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == 119 || keycode == 65362)
		data->keys.w = 0;
	if (keycode == 115 || keycode == 65364)
		data->keys.s = 0;
	if (keycode == 97)
		data->keys.a = 0;
	if (keycode == 100)
		data->keys.d = 0;
	if (keycode == 65361)
		data->keys.left = 0;
	if (keycode == 65363)
		data->keys.right = 0;
	return (0);
}

void	rotate_player(t_data *data, double angle)
{
	double		old_dir_x;
	double		old_plane_x;
	t_player	*p;

	p = &data->player;
	old_dir_x = p->dir.x;
	p->dir.x = p->dir.x * cos(angle) - p->dir.y * sin(angle);
	p->dir.y = old_dir_x * sin(angle) + p->dir.y * cos(angle);
	old_plane_x = p->plane.x;
	p->plane.x = p->plane.x * cos(angle) - p->plane.y * sin(angle);
	p->plane.y = old_plane_x * sin(angle) + p->plane.y * cos(angle);
}
