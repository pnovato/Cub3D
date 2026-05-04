/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 22:30:00 by kali              #+#    #+#             */
/*   Updated: 2026/05/04 06:34:22 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	int		offset;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	offset = (y * data->init.size_line) + (x * (data->init.bits_p_pixel / 8));
	dst = data->init.addr + offset;
	*(unsigned int *)dst = color;
}

int	get_texture_pixel(t_texture *tex, int x, int y)
{
	char	*dst;
	int		offset;

	if (x < 0 || x >= tex->t_width || y < 0 || y >= tex->t_height)
		return (0);
	offset = (y * tex->size_line) + (x * (tex->bits_p_pixel / 8));
	dst = tex->addr_img + offset;
	return (*(unsigned int *)dst);
}
