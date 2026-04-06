#include "../../includes/cub3d.h"

void	close_window(t_data *data)
{
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
	if (keycode == 65307) // ESC
		handle_close(data);
	if (keycode == 119 || keycode == 65362) // W ou Seta Cima
		data->keys.w = 1;
	if (keycode == 115 || keycode == 65364) // S ou Seta Baixo
		data->keys.s = 1;
	if (keycode == 97)                      // A
		data->keys.a = 1;
	if (keycode == 100)                     // D
		data->keys.d = 1;
	if (keycode == 65361)                   // Seta Esquerda
		data->keys.left = 1;
	if (keycode == 65363)                   // Seta Direita
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

void	init_window(t_data *data)
{
	data->init.mlx_ptr = mlx_init();
	if (!data->init.mlx_ptr)
		exit(1);
	data->init.win_ptr = mlx_new_window(data->init.mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	data->init.img_ptr = mlx_new_image(data->init.mlx_ptr, WIDTH, HEIGHT);
	data->init.addr = mlx_get_data_addr(data->init.img_ptr, &data->init.bits_p_pixel, 
									 &data->init.size_line, &data->init.endian);

	// Hook para fechar no X da janela
	mlx_hook(data->init.win_ptr, 17, 0, (int (*)())(void *)handle_close, data);
	
	// Hook para Tecla Pressionada
	mlx_hook(data->init.win_ptr, 2, 1L << 0, (int (*)())(void *)key_press, data);
	
	// Hook para Tecla Solta
	mlx_hook(data->init.win_ptr, 3, 1L << 1, (int (*)())(void *)key_release, data);
}
