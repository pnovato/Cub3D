#ifndef CUB3D_H
# define CUB3D_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <mlx.h>
# include "../libft/libft.h"

# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_cub
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_cub;


// init_mlx.c
void	init_window(t_cub *vars);
void	close_window(t_cub *vars);
int	handle_close(t_cub *vars);
int	handle_key(int keycode, t_cub *vars);
//int     key_press(int keycode, t_cub *vars);

#endif
