#include "../../includes/cub3d.h"

static int	check_elements(t_data *data)
{
	if (!data->map.path_no)
		return (printf("Error\nMissing NO texture\n"), 1);
	if (!data->map.path_so)
		return (printf("Error\nMissing SO texture\n"), 1);
	if (!data->map.path_we)
		return (printf("Error\nMissing WE texture\n"), 1);
	if (!data->map.path_ea)
		return (printf("Error\nMissing EA texture\n"), 1);
	if (!data->floor_color && data->floor_color != 0)
		return (printf("Error\nMissing F color\n"), 1);
	if (!data->ceiling_color && data->ceiling_color != 0)
		return (printf("Error\nMissing C collor\n"), 1);
	return (0);
}

static char	*parse_config(int fd, t_data *data)
{
	char	*line;
	int	ret;

	line = get_next_line(fd);
	while (line)
	{
		ret = parse_element(line, data);
		free(line);
		if (ret == 1)
			return (NULL);
		if (ret == 2)
		{
			line = get_next_line(fd);
			return (line);
		}
		line = get_next_line(fd);
	}
	return (NULL);
}

static int	read_map_line(int fd, t_data *data, char *first_line)
{
	char	*line;
	char	**temp; //temp variable so we don't lose pointer if temp is bad allocated
	int	i;
	
	data->map.map = malloc(sizeof(char *) * 2); //space for the line and the NULL character
	if (!data->map.map)
		return (1);
	i = 0;
	line = first_line;
	while (line)
	{
		temp = realloc(data->map.map, sizeof(char *) * (i + 2)); //same as above
		if (!temp)
		{
			free(line);
			return (printf("Error\nBad memory allocation in function read_map_line\n"), 1);
		}
		data->map.map = temp;
		data->map.map[i] = ft_strtrim(line, "\n");
		free(line);
		i++;
		line = get_next_line(fd);
	}
	data->map.map[i] = NULL;
	data->map.n_lines = i;
	return (0);
}

int	parse_map(char *file, t_data *data)
{
	int	fd;
	char	*first_map_line;
	
	if (ft_strncmp(file + ft_strlen(file) - 4, ".cub", 4))
		return (printf("Error\nFile must be a \".cub\" extension"), 1);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nFile not opening\n"), 1);
	first_map_line = parse_config(fd, data);
	if (check_elements(data))
		return (close(fd), 1);
	if (read_map_line(fd, data, first_map_line))
		return(close(fd), printf("Error\nError when reading map\n"), 1);
	close(fd);
	//validate if has player and if map is closed
	return (0);
}
