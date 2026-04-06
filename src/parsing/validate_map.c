#include "../../includes/cub3d.h"

static int	is_valid_char(int c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'W'
			|| c == 'E' || c == ' ');
}

static int	check_char(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map.map[i])
	{
		j = 0;
		while (data->map.map[i][j])
		{
			if (!is_valid_char(data->map.map[i][j])
				return (printf("Error\nInvalid map char '%c'\n",
					data->map.map[i][j]), 1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	find_player(t_data *data)
{
	int	i;
	int	j;
	int	count;
	
	count = 0;
	i = 0;
	while (data->map.map[i])
	{
		j = 0;
		while (data->map.map[i][j])
		{
			if (data->map.map[i][j] == 'N' || data->map.map[i][j] == 'S'
			|| data->map.map[i][j] == 'W' || data->map.map[i][j] == 'E')
			{
				count++;
				data->player.pos.x = j + 0.5; //this places the player in the middle of the cell
				data->player.pos.y = i + 0.5; //same as above
				data->player.spawn_dir = data->map.map[i][j];
				data->map.map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	if (count == 0)
		return (printf("Error\nNo player found\n"), 1);
	if (count > 1)
		return (printf("Error\nMore then one player found\n"), 1);
	return (0);
}

static int	check_cell(t_data *data, int i, int j)
{
	int	max_j;
	
	if (data->map.map[i][j] == '\0')
		return (0);
	if (i == 0)
		return (printf("Error\nMap is not closed\n"), 1);
	if (!data->map.map[i + 1])
		return (printf("Error\nMap is not closed\n", 1);
	if (j == 0)
		return (printf("Error\nMap is not closed\n", 1);
	max_j = ft_strlen(data->map.map[i]);
	if (j >= max_j - 1)
		return (printf("Error\nMap is not closed\n", 1);
	if (data->map.map[i - 1][j] == ' ' || data->map.map[i - 1][j] == '\0')
		return (printf("Error\nMap is not closed\n", 1);
	if (data->map.map[i + 1][j] == ' ' || data->map.map[i + 1][j] == '\0')
		return (printf("Error\nMap is not closed\n", 1);
	if (data->map.map[i][j - 1] == ' ')
		return (printf("Error\nMap is not closed\n", 1);
	if (data->map.map[i][j + 1] == ' ' || data->map.map[i][j + 1] == '\0')
		return (printf("Error\nMap is not closed\n", 1);
	return (0);
}

static int 	check_closed(t_data *data)
{
	int	i;
	int	j;
	
	i = 0;
	while (data->map.map[i])
	{
		j = 0;
		while (data->map.map[i][j])
		{
			if (check_cell(data, i, j)
				return (1);
			j++;
		}
		i++;	
	}
	return (0);
}

int	validate_map(t_data *data)
{
	if (check_char(data))
		return (1);
	if (find_player(data))
		return (1);
	if (check_closed(data))
		return (1);
	return (0);
}

