/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 21:36:12 by kali              #+#    #+#             */
/*   Updated: 2026/05/04 07:29:14 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	close_window(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->text[i].img_ptr)
			mlx_destroy_image(data->init.mlx_ptr, data->text[i].img_ptr);
		i++;
	}
	if (data->floor.img_ptr)
		mlx_destroy_image(data->init.mlx_ptr, data->floor.img_ptr);
	if (data->ceiling.img_ptr)
		mlx_destroy_image(data->init.mlx_ptr, data->ceiling.img_ptr);
	mlx_do_key_autorepeaton(data->init.mlx_ptr);
	free_data(data);
	exit(0);
}

int	handle_close(t_data *data)
{
	close_window(data);
	return (0);
}

static void	load_single_texture(t_data *data, t_texture *t, char *path)
{
	t->img_ptr = mlx_xpm_file_to_image(data->init.mlx_ptr, path,
			&t->t_width, &t->t_height);
	if (!t->img_ptr)
	{
		printf("Error\nTexture load fail: %s\n", path);
		exit(1);
	}
	t->addr_img = mlx_get_data_addr(t->img_ptr, &t->bits_p_pixel,
			&t->size_line, &t->endian);
}

static void	init_textures(t_data *data)
{
	load_single_texture(data, &data->text[NO], data->map.path_no);
	load_single_texture(data, &data->text[SO], data->map.path_so);
	load_single_texture(data, &data->text[WE], data->map.path_we);
	load_single_texture(data, &data->text[EA], data->map.path_ea);
	load_single_texture(data, &data->floor, "./textures/grass.xpm");
	load_single_texture(data, &data->ceiling, "./textures/sky.xpm");
}

void	init_window(t_data *data)
{
	void	*win;

	data->init.mlx_ptr = mlx_init();
	if (!data->init.mlx_ptr)
		exit(1);
	init_textures(data);
	data->init.win_ptr = mlx_new_window(data->init.mlx_ptr, WIDTH,
			HEIGHT, "Cub3D");
	win = data->init.win_ptr;
	data->init.img_ptr = mlx_new_image(data->init.mlx_ptr, WIDTH, HEIGHT);
	data->init.addr = mlx_get_data_addr(data->init.img_ptr,
			&data->init.bits_p_pixel, &data->init.size_line,
			&data->init.endian);
	mlx_hook(win, 17, 0, (int (*)())(void *)handle_close, data);
	mlx_hook(win, 2, 1L << 0, (int (*)())(void *)key_press, data);
	mlx_hook(win, 3, 1L << 1, (int (*)())(void *)key_release, data);
	mlx_do_key_autorepeatoff(data->init.mlx_ptr);
	mlx_loop_hook(data->init.mlx_ptr, (int (*)())(void *)render_frame, data);
}
