/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 21:39:58 by kali              #+#    #+#             */
/*   Updated: 2026/04/09 21:40:00 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	free_map(t_data *data)
{
	int	i;

	if (data->map.map)
	{
		i = 0;
		while (data->map.map[i])
			free(data->map.map[i++]);
		free(data->map.map);
		data->map.map = NULL;
	}
	if (data->map.path_no)
		free(data->map.path_no);
	if (data->map.path_so)
		free(data->map.path_so);
	if (data->map.path_we)
		free(data->map.path_we);
	if (data->map.path_ea)
		free(data->map.path_ea);
}

static void	free_mlx(t_data *data)
{
	if (data->init.img_ptr)
		mlx_destroy_image(data->init.mlx_ptr, data->init.img_ptr);
	if (data->init.win_ptr)
		mlx_destroy_window(data->init.mlx_ptr, data->init.win_ptr);
	if (data->init.mlx_ptr)
	{
		mlx_destroy_display(data->init.mlx_ptr);
		free(data->init.mlx_ptr);
	}
}

void	free_data(t_data *data)
{
	free_map(data);
	free_mlx(data);
}
