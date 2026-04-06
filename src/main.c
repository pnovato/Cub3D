#include "../includes/cub3d.h"

void    free_data(t_data *data)
{
    int i;

    // Liberta o mapa
    if (data->map.map)
    {
        i = 0;
        while (data->map.map[i])
            free(data->map.map[i++]);
        free(data->map.map);
    }
    // Destrói a imagem MLX
    if (data->init.img_ptr)
        mlx_destroy_image(data->init.mlx_ptr, data->init.img_ptr);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
	{
		printf("Error\nUso correto: ./cub3d <caminho_do_mapa.cub>\n");
		return (1);
	}

	// Limpa toda a struct (zera as teclas, ponteiros, etc)
	ft_bzero(&data, sizeof(t_data));

	// 1. Parser: Lê o arquivo e preenche o mapa
	if (parse_map(av[1], &data))
		return (1);
	init_player_dir(&data);
	init_window(&data);
	init_window(&data);
	mlx_loop_hook(data.init.mlx_ptr, (int (*)())(void *)render_frame, &data);
	mlx_loop(data.init.mlx_ptr);

	return (0);
}
