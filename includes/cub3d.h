#ifndef CUB3D_H
# define CUB3D_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include "mlx.h"
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
	EA
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
    void    *mlx_ptr;
    void    *win_ptr;
    void    *img_ptr;
    char    *addr;         
    int     bits_p_pixel;  
    int     size_line;     
    int     endian;        
}   t_cub;
//---------------------------------------------------------
//Struct for the map (pointer to matrix, number of lines n columns)
//---------------------------------------------------------
typedef struct s_map
{
	char	**map;
	int	n_lines;
	int	n_column;
	char	*path_no; //path to texture NO
	char	*path_so;
	char	*path_we;
	char	*path_ea;
}	t_map;
//---------------------------------------------------------
//Struct for the player (Working with vectors)
//---------------------------------------------------------
typedef struct s_player
{
	struct s_vector	pos;
	struct s_vector	dir;
	struct s_vector	plane;
	char		spawn_dir;
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

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;
//--------------------------------------------------------
//The only struct that's going to be called during the project
//cause it has an instance of all others inside it. 
//--------------------------------------------------------
typedef struct s_data
{
	t_cub		init;
	t_map		map;
	t_player	player;
	t_ray		ray;
	t_texture	text[4];
	t_keys		keys;
	int			floor_color;
	int			ceiling_color;
}	t_data;

// init_mlx.c
void	init_window(t_data *data);
void	close_window(t_data *data);
int	handle_close(t_data *data);
int	handle_key(int keycode, t_data *vars);
int     parse_map(char *file, t_data *data);
int     render_frame(t_data *data);
//int     key_press(int keycode, t_cub *vars);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_vertical_line(t_data *data, int x, int draw_start, int draw_end);
void	rotate_player(t_data *data, double angle);
char	*get_next_line(int fd);
void    free_data(t_data *data);

int	parse_element(char *line, t_data *data);
int     validate_map(t_data *data);

void    init_player_dir(t_data *data);
void	free_data(t_data *data);

#endif
