#include "../../includes/cub3d.h"

void	close_window(t_cub *vars)
{
	if (vars->win_ptr)
		mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
	if (vars->mlx_ptr)
		free(vars->mlx_ptr);
	exit(0);
}

int	handle_key(int keycode, t_cub *vars)
{
	if (keycode == 65307)
		close_window(vars);
	return (0);
}

int	handle_close(t_cub *vars)
{
	close_window(vars);
	return (0);
}

void	init_window(t_cub *vars)
{
	vars->mlx_ptr = mlx_init();
	if (!vars->mlx_ptr)
		exit(1);
	vars->win_ptr = mlx_new_window(vars->mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	if (!vars->win_ptr)
		exit(1);
}
