/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 21:47:48 by kali              #+#    #+#             */
/*   Updated: 2026/05/04 10:32:48 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	draw_sky_fast(t_data *data, int x, int y, int tx)
{
	int	ty;

	ty = (y * data->ceiling.t_height) / (HEIGHT / 2);
	if (ty < 0)
		ty = 0;
	if (ty >= data->ceiling.t_height)
		ty = data->ceiling.t_height - 1;
	my_mlx_pixel_put(data, x, y, get_texture_pixel(&data->ceiling, tx, ty));
}

static void	draw_floor_fast(t_data *data, int x, int y)
{
	double	f[3];
	int		t[2];
	double	p_w;
	double	px;
	double	py;

	px = data->player.pos.x;
	py = data->player.pos.y;
	f[0] = data->ray.map_x + data->ray.wallx;
	f[1] = data->ray.map_y + data->ray.wallx;
	if (data->ray.side_hit == 0)
		f[0] = data->ray.map_x + (data->ray.dir_ray.x < 0);
	else
		f[1] = data->ray.map_y + (data->ray.dir_ray.y < 0);
	p_w = y - HEIGHT / 2.0;
	if (p_w == 0)
		p_w = 1;
	f[2] = (HEIGHT / (2.0 * p_w)) / data->ray.perp_wall_dist;
	t[0] = (int)((f[2] * f[0] + (1.0 - f[2]) * px) * data->floor.t_width);
	t[1] = (int)((f[2] * f[1] + (1.0 - f[2]) * py) * data->floor.t_height);
	t[0] = (t[0] % data->floor.t_width + data->floor.t_width);
	t[0] %= data->floor.t_width;
	t[1] = (t[1] % data->floor.t_height + data->floor.t_height);
	t[1] %= data->floor.t_height;
	my_mlx_pixel_put(data, x, y, get_texture_pixel(&data->floor, t[0], t[1]));
}

static void	draw_wall_fast(t_data *data, int x, int y)
{
	int		texy;
	int		color;
	t_ray	*r;

	r = &data->ray;
	texy = (int)(r->texpos) & (data->text[r->tex_idx].t_height - 1);
	r->texpos += r->step;
	color = get_texture_pixel(&data->text[r->tex_idx], r->texx, texy);
	if (r->side_hit == 1)
		color = (color >> 1) & 8355711;
	my_mlx_pixel_put(data, x, y, color);
}

void	draw_vertical_line(t_data *data, int x)
{
	int		y;
	int		sky_tx;
	double	angle;
	t_ray	*r;

	r = &data->ray;
	angle = atan2(r->dir_ray.y, r->dir_ray.x);
	sky_tx = (int)((angle + M_PI) / (2.0 * M_PI) * data->ceiling.t_width);
	sky_tx = (sky_tx % data->ceiling.t_width + data->ceiling.t_width);
	sky_tx %= data->ceiling.t_width;
	r->step = 1.0 * data->text[r->tex_idx].t_height / r->line_height;
	r->texpos = (r->draw_start - HEIGHT / 2.0 + r->line_height / 2.0) * r->step;
	y = 0;
	while (y < HEIGHT)
	{
		if (y < r->draw_start)
			draw_sky_fast(data, x, y, sky_tx);
		else if (y >= r->draw_start && y <= r->draw_end)
			draw_wall_fast(data, x, y);
		else
			draw_floor_fast(data, x, y);
		y++;
	}
}
