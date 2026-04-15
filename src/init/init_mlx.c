/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 21:36:12 by kali              #+#    #+#             */
/*   Updated: 2026/04/09 21:39:52 by kali             ###   ########.fr       */
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
	free_data(data);
	exit(0);
}

int	handle_close(t_data *data)
{
	close_window(data);
	return (0);
}

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
	double old_dir_x = data->player.dir.x;
	data->player.dir.x = data->player.dir.x * cos(angle) - data->player.dir.y * sin(angle);
	data->player.dir.y = old_dir_x * sin(angle) + data->player.dir.y * cos(angle);
	double old_plane_x = data->player.plane.x;
	data->player.plane.x = data->player.plane.x * cos(angle) - data->player.plane.y * sin(angle);
	data->player.plane.y = old_plane_x * sin(angle) + data->player.plane.y * cos(angle);
}

void	load_texture(t_data *data, int idx, char *path)
{
	data->text[idx].img_ptr = mlx_xpm_file_to_image(data->init.mlx_ptr, path, 
													&data->text[idx].t_width,
													&data->text[idx].t_height);
	if (!data->text[idx].img_ptr)
	{
		printf("Error\nFalha ao carregar textura: %s\n", path);
		exit(1);
	}
	data->text[idx].addr_img = mlx_get_data_addr(data->text[idx].img_ptr, 
												&data->text[idx].bits_p_pixel, 
												&data->text[idx].size_line, 
												&data->text[idx].endian);
}

void	load_single_texture(t_data *data, t_texture *tex, char *path)
{
	tex->img_ptr = mlx_xpm_file_to_image(data->init.mlx_ptr, path, 
										&tex->t_width, &tex->t_height);
	if (!tex->img_ptr)
	{
		printf("Error\nFalha ao carregar textura: %s\n", path);
		exit(1);
	}
	tex->addr_img = mlx_get_data_addr(tex->img_ptr, &tex->bits_p_pixel, 
									&tex->size_line, &tex->endian);
}

void	init_textures(t_data *data)
{
	char *p_no = data->map.path_no ? data->map.path_no : "./textures/north.xpm";
	char *p_so = data->map.path_so ? data->map.path_so : "./textures/south.xpm";
	char *p_we = data->map.path_we ? data->map.path_we : "./textures/west.xpm";
	char *p_ea = data->map.path_ea ? data->map.path_ea : "./textures/east.xpm";

	load_single_texture(data, &data->text[NO], p_no);
	load_single_texture(data, &data->text[SO], p_so);
	load_single_texture(data, &data->text[WE], p_we);
	load_single_texture(data, &data->text[EA], p_ea);
	load_single_texture(data, &data->floor, "./textures/grass.xpm");
	load_single_texture(data, &data->ceiling, "./textures/sky.xpm");
}

void	init_window(t_data *data)
{
	data->init.mlx_ptr = mlx_init();
	if (!data->init.mlx_ptr)
		exit(1);
	init_textures(data);
	data->init.win_ptr = mlx_new_window(data->init.mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	data->init.img_ptr = mlx_new_image(data->init.mlx_ptr, WIDTH, HEIGHT);
	data->init.addr = mlx_get_data_addr(data->init.img_ptr, &data->init.bits_p_pixel, 
									 &data->init.size_line, &data->init.endian);
	mlx_hook(data->init.win_ptr, 17, 0, (int (*)())(void *)handle_close, data);
	mlx_hook(data->init.win_ptr, 2, 1L << 0, (int (*)())(void *)key_press, data);
	mlx_hook(data->init.win_ptr, 3, 1L << 1, (int (*)())(void *)key_release, data);
}
