/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 06:32:32 by kali              #+#    #+#             */
/*   Updated: 2026/05/04 07:11:00 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	calc_line_height(t_data *data)
{
	t_ray	*r;

	r = &data->ray;
	if (r->side_hit == 0)
		r->perp_wall_dist = r->side_dist_x - r->delt_x;
	else
		r->perp_wall_dist = r->side_dist_y - r->delt_y;
	if (r->perp_wall_dist <= 0)
		r->perp_wall_dist = 0.1;
	r->line_height = (int)(HEIGHT / r->perp_wall_dist);
	r->draw_start = -r->line_height / 2 + HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + HEIGHT / 2;
	if (r->draw_end >= HEIGHT)
		r->draw_end = HEIGHT - 1;
}

static void	calc_texture(t_data *data)
{
	t_ray		*r;
	t_player	*p;
	int			tw;

	r = &data->ray;
	p = &data->player;
	if (r->side_hit == 0)
		r->wallx = p->pos.y + r->perp_wall_dist * r->dir_ray.y;
	else
		r->wallx = p->pos.x + r->perp_wall_dist * r->dir_ray.x;
	r->wallx -= floor(r->wallx);
	if (r->side_hit == 0 && r->dir_ray.x > 0)
		r->tex_idx = WE;
	else if (r->side_hit == 0)
		r->tex_idx = EA;
	else if (r->side_hit == 1 && r->dir_ray.y > 0)
		r->tex_idx = NO;
	else
		r->tex_idx = SO;
	tw = data->text[r->tex_idx].t_width;
	r->texx = (int)(r->wallx * (double)tw);
	if (r->side_hit == 0 && r->dir_ray.x > 0)
		r->texx = tw - r->texx - 1;
	if (r->side_hit == 1 && r->dir_ray.y < 0)
		r->texx = tw - r->texx - 1;
}

int	render_frame(t_data *data)
{
	int		x;
	void	*m;
	void	*w;
	void	*img;

	m = data->init.mlx_ptr;
	w = data->init.win_ptr;
	img = data->init.img_ptr;
	move_player(data);
	x = 0;
	while (x < WIDTH)
	{
		init_ray(data, x);
		calc_step(data);
		perform_dda(data);
		calc_line_height(data);
		calc_texture(data);
		draw_vertical_line(data, x);
		x++;
	}
	mlx_put_image_to_window(m, w, img, 0, 0);
	return (0);
}
