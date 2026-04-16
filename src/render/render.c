/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 21:58:54 by kali              #+#    #+#             */
/*   Updated: 2026/04/09 22:05:36 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* ** 1. Inicializa as variáveis do raio para a coluna atual (x)
*/
static void	init_ray(t_data *data, int x)
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

static void	calc_step(t_data *data)
{
	if (data->ray.dir_ray.x < 0)
	{
		data->ray.step_x = -1;
		data->ray.side_dist_x = (data->player.pos.x - data->ray.map_x) * data->ray.delt_x;
	}
	else
	{
		data->ray.step_x = 1;
		data->ray.side_dist_x = (data->ray.map_x + 1.0 - data->player.pos.x) * data->ray.delt_x;
	}
	if (data->ray.dir_ray.y < 0)
	{
		data->ray.step_y = -1;
		data->ray.side_dist_y = (data->player.pos.y - data->ray.map_y) * data->ray.delt_y;
	}
	else
	{
		data->ray.step_y = 1;
		data->ray.side_dist_y = (data->ray.map_y + 1.0 - data->player.pos.y) * data->ray.delt_y;
	}
}

static void	perform_dda(t_data *data)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (data->ray.side_dist_x < data->ray.side_dist_y)
		{
			data->ray.side_dist_x += data->ray.delt_x;
			data->ray.map_x += data->ray.step_x;
			data->ray.side_hit = 0; // Parede Leste/Oeste
		}
		else
		{
			data->ray.side_dist_y += data->ray.delt_y;
			data->ray.map_y += data->ray.step_y;
			data->ray.side_hit = 1; // Parede Norte/Sul
		}
		if (data->map.map[data->ray.map_y][data->ray.map_x] == '1')
			hit = 1;
	}
}

/* ** 4. Calcula a distância real e os limites de desenho na tela
*/
static void	calc_line_height(t_data *data, int *line_height, int *draw_start, int *draw_end)
{
	if (data->ray.side_hit == 0)
		data->ray.perp_wall_dist = (data->ray.side_dist_x - data->ray.delt_x);
	else
		data->ray.perp_wall_dist = (data->ray.side_dist_y - data->ray.delt_y);
	if (data->ray.perp_wall_dist <= 0)
		data->ray.perp_wall_dist = 0.1;
	*line_height = (int)(HEIGHT / data->ray.perp_wall_dist);
	*draw_start = -(*line_height) / 2 + HEIGHT / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = (*line_height) / 2 + HEIGHT / 2;
	if (*draw_end >= HEIGHT)
		*draw_end = HEIGHT - 1;
}

void	move_player(t_data *data)
{
	double s = 0.05;
	double r = 0.04;

	if (data->keys.w)
	{
		if (data->map.map[(int)data->player.pos.y][(int)(data->player.pos.x + data->player.dir.x * s)] != '1')
			data->player.pos.x += data->player.dir.x * s;
		if (data->map.map[(int)(data->player.pos.y + data->player.dir.y * s)][(int)data->player.pos.x] != '1')
			data->player.pos.y += data->player.dir.y * s;
	}
	if (data->keys.s)
	{
		if (data->map.map[(int)data->player.pos.y][(int)(data->player.pos.x - data->player.dir.x * s)] != '1')
			data->player.pos.x -= data->player.dir.x * s;
		if (data->map.map[(int)(data->player.pos.y - data->player.dir.y * s)][(int)data->player.pos.x] != '1')
			data->player.pos.y -= data->player.dir.y * s;
	}
	if (data->keys.a)
	{
		if (data->map.map[(int)data->player.pos.y][(int)(data->player.pos.x - data->player.plane.x * s)] != '1')
			data->player.pos.x -= data->player.plane.x * s;
		if (data->map.map[(int)(data->player.pos.y - data->player.plane.y * s)][(int)data->player.pos.x] != '1')
			data->player.pos.y -= data->player.plane.y * s;
	}
	if (data->keys.d)
	{
		if (data->map.map[(int)data->player.pos.y][(int)(data->player.pos.x + data->player.plane.x * s)] != '1')
			data->player.pos.x += data->player.plane.x * s;
		if (data->map.map[(int)(data->player.pos.y + data->player.plane.y * s)][(int)data->player.pos.x] != '1')
			data->player.pos.y += data->player.plane.y * s;
	}
	if (data->keys.left)
		rotate_player(data, -r);
	if (data->keys.right)
		rotate_player(data, r);
}

int	render_frame(t_data *data)
{
	int	x;
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	tex_idx;

	move_player(data);
	x = 0;
	while (x < WIDTH)
	{
		init_ray(data, x);
		calc_step(data);
		perform_dda(data);
		calc_line_height(data, &line_height, &draw_start, &draw_end);
		if (data->ray.side_hit == 0)
			data->ray.wallx = data->player.pos.y + data->ray.perp_wall_dist * data->ray.dir_ray.y;
		else
			data->ray.wallx = data->player.pos.x + data->ray.perp_wall_dist * data->ray.dir_ray.x;
		data->ray.wallx -= floor(data->ray.wallx);
		if (data->ray.side_hit == 0)
			tex_idx = (data->ray.dir_ray.x > 0) ? WE : EA;
		else
			tex_idx = (data->ray.dir_ray.y > 0) ? NO : SO;
		data->ray.texx = (int)(data->ray.wallx * (double)data->text[tex_idx].t_width);
		if (data->ray.side_hit == 0 && data->ray.dir_ray.x > 0)
			data->ray.texx = data->text[tex_idx].t_width - data->ray.texx - 1;
		if (data->ray.side_hit == 1 && data->ray.dir_ray.y < 0)
			data->ray.texx = data->text[tex_idx].t_width - data->ray.texx - 1;
		draw_vertical_line(data, x, draw_start, draw_end, line_height, tex_idx);
		x++;
	}
	mlx_put_image_to_window(data->init.mlx_ptr, data->init.win_ptr, data->init.img_ptr, 0, 0);
	return (0);
}