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

typedef enum e_dir
{
    N,
    S,
    W,
    E
}   t_dir;

typedef struct s_cub
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
}	t_cub;

typedef struct s_texture
{
	char		*addr_img;
	void		*img_ptr;
	int		bits_p_pixel;
	int		size_line;
	int		endian;
	int		t_height;
	int		t_width;
}	t_texture;
	

// init_mlx.c
void	init_window(t_cub *vars);
void	close_window(t_cub *vars);
int	handle_close(t_cub *vars);
int	handle_key(int keycode, t_cub *vars);
//int     key_press(int keycode, t_cub *vars);

#endif
