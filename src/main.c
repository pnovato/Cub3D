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

	// 2. Player: Define posição e direção inicial (Manual por enquanto)
	data.player.pos.x = 5.5; 
	data.player.pos.y = 4.5;
	data.player.dir.x = 0.0; data.player.dir.y = -1.0; // Olhando para o Norte
	data.player.plane.x = 0.66; data.player.plane.y = 0.0;

	// 3. MLX: Inicializa a janela e os ganchos (Hooks)
	// Passamos &data (t_data*) e não &data.init
	init_window(&data);

	// 4. Loop: O render_frame será chamado sem parar
	// Usamos o cast (int (*)()) para evitar erros de -Werror
	mlx_loop_hook(data.init.mlx_ptr, (int (*)())(void *)render_frame, &data);

	// 5. Inicia o loop infinito da MLX
	mlx_loop(data.init.mlx_ptr);

	return (0);
}
