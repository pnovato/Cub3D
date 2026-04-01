#include "../../includes/cub3d.h"

/* ** Função clássica da miniLibX para pintar um pixel na memória da imagem
** Nota: Você vai precisar ter o endereço dos dados da imagem principal (addr) 
** salvo na sua struct para isso funcionar rápido.
*/
void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    // Proteção essencial: impede de desenhar fora da tela (Segfault)
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return ;

    // Vai buscar o endereço exato do pixel usando os dados da init (t_cub)
    dst = data->init.addr + (y * data->init.size_line + x * (data->init.bits_p_pixel / 8));
    
    // Altera a cor na memória
    *(unsigned int*)dst = color;
}

/* ** Função que desenha a linha vertical completa: Teto, Parede e Chão
*/
void	draw_vertical_line(t_data *data, int x, int draw_start, int draw_end)
{
	int	y;
	int	color_ceiling;
	int	color_floor;
	int	color_wall;

	// Cores provisórias (Hexadecimal RGB) para você testar
	color_ceiling = 0x87CEEB; // Azul céu
	color_floor = 0x8B4513;   // Marrom terra
	color_wall = 0x00FF00;    // Verde choque para a parede

	// Se o raio bateu numa parede Norte/Sul, fazemos a cor um pouco mais escura
	// para dar um efeito falso de sombra 3D!
	if (data->ray.side_hit == 1)
		color_wall = 0x00CC00; 

	y = 0;
	while (y < HEIGHT)
	{
		if (y < draw_start)
			my_mlx_pixel_put(data, x, y, color_ceiling); // Desenha o teto
		else if (y >= draw_start && y <= draw_end)
			my_mlx_pixel_put(data, x, y, color_wall);    // Desenha a parede
		else
			my_mlx_pixel_put(data, x, y, color_floor);   // Desenha o chão
		y++;
	}
}