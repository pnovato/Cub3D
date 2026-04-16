/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 21:47:48 by kali              #+#    #+#             */
/*   Updated: 2026/04/09 22:09:47 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = data->init.addr + (y * data->init.size_line + x * (data->init.bits_p_pixel / 8));
	*(unsigned int *)dst = color;
}

/* ** Função que desenha a linha vertical completa: Teto, Parede e Chão
*/
int	get_texture_pixel(t_texture *tex, int x, int y)
{
	char	*dst;
	int		color;

	if (x < 0 || x >= tex->t_width || y < 0 || y >= tex->t_height)
		return (0);
	dst = tex->addr_img + (y * tex->size_line + x * (tex->bits_p_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}

void	draw_vertical_line(t_data *data, int x, int draw_start, int draw_end, int line_height, int tex_idx)
{
	int		y;
	int		color;
	double	step;
	double	texpos;
	double	floorxwall;
	double	floorywall;

	if (data->ray.side_hit == 0 && data->ray.dir_ray.x > 0)
	{
		floorxwall = data->ray.map_x;
		floorywall = data->ray.map_y + data->ray.wallx;
	}
	else if (data->ray.side_hit == 0 && data->ray.dir_ray.x < 0)
	{
		floorxwall = data->ray.map_x + 1.0;
		floorywall = data->ray.map_y + data->ray.wallx;
	}
	else if (data->ray.side_hit == 1 && data->ray.dir_ray.y > 0)
	{
		floorxwall = data->ray.map_x + data->ray.wallx;
		floorywall = data->ray.map_y;
	}
	else
	{
		floorxwall = data->ray.map_x + data->ray.wallx;
		floorywall = data->ray.map_y + 1.0;
	}
	step = 1.0 * data->text[tex_idx].t_height / line_height;
	texpos = (draw_start - HEIGHT / 2.0 + line_height / 2.0) * step;
	double ray_angle = atan2(data->ray.dir_ray.y, data->ray.dir_ray.x);
	int sky_tX = (int)((ray_angle + M_PI) / (2.0 * M_PI) * data->ceiling.t_width);
	if (sky_tX < 0)
		sky_tX += data->ceiling.t_width;
	if (sky_tX >= data->ceiling.t_width)
		sky_tX %= data->ceiling.t_width;
	y = 0;
	while (y < HEIGHT)
	{
		if (y < draw_start)
		{
			int sky_tY = (y * data->ceiling.t_height) / (HEIGHT / 2);
			if (sky_tY < 0)
				sky_tY = 0;
			if (sky_tY >= data->ceiling.t_height)
				sky_tY = data->ceiling.t_height - 1;
			color = get_texture_pixel(&data->ceiling, sky_tX, sky_tY);
			my_mlx_pixel_put(data, x, y, color);
		}
		else if (y >= draw_start && y <= draw_end)
		{
			int texy = (int)texpos & (data->text[tex_idx].t_height - 1);
			texpos += step;
			color = get_texture_pixel(&data->text[tex_idx], data->ray.texx, texy);
			if (data->ray.side_hit == 1)
				color = (color >> 1) & 8355711;
			my_mlx_pixel_put(data, x, y, color);
		}
		else
		{
			int p = y - HEIGHT / 2;
			if (p == 0) p = 1;
			double weight = (HEIGHT / (2.0 * p)) / data->ray.perp_wall_dist;
			double currentFloorX = weight * floorxwall + (1.0 - weight) * data->player.pos.x;
			double currentFloorY = weight * floorywall + (1.0 - weight) * data->player.pos.y;
			int tX = (int)(currentFloorX * data->floor.t_width) % data->floor.t_width;
			int tY = (int)(currentFloorY * data->floor.t_height) % data->floor.t_height;
			if (tX < 0) tX += data->floor.t_width;
			if (tY < 0) tY += data->floor.t_height;
			color = get_texture_pixel(&data->floor, tX, tY);
			my_mlx_pixel_put(data, x, y, color);
		}
		y++;
	}
}
