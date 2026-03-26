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

//---------------------------------------------------------
//Texture according to coordinates
//---------------------------------------------------------
typedef enum e_dir
{
	NO,
	SO,
	WE,
	EA,
	F,
	C
}   t_dir;
//---------------------------------------------------------
//Struct base for vector calculations
//---------------------------------------------------------
typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;
//---------------------------------------------------------
//Struct for window initialization and events
//---------------------------------------------------------
typedef struct s_cub
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
}	t_cub;
//---------------------------------------------------------
//Struct for the map (pointer to matrix, number of lines n columns)
//---------------------------------------------------------
typedef struct s_map
{
	char	**map;
	int	n_lines;
	int	n_column;
}	t_map;
//---------------------------------------------------------
//Struct for the player (Working with vectors)
//---------------------------------------------------------
typedef struct s_player
{
	struct s_vector	pos;
	struct s_vector	dir;
	struct s_vector	plane;
}	t_player;
//---------------------------------------------------------
//Struct for the data required for every ray loop
//---------------------------------------------------------
typedef struct s_ray
{
	t_vector dir_ray;
	int	map_x;
	int	map_y;
	int	side_hit;
	int	step_x;
	int	step_y;
	double	delt_x;
	double	delt_y;
	double	side_dist_x;
	double	side_dist_y;
	double	perp_wall_dist;
}	t_ray;
//---------------------------------------------------------
//Struct for the textures (All related to the function 
//char *mlx_get_data_addr which is going to work with the
//raw data of the image
//---------------------------------------------------------
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
