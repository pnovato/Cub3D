#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_cub	vars;
	init_window(&vars);
	mlx_loop(vars.mlx_ptr);
	return (0);
}
