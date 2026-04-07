#include "../../includes/cub3d.h"

static char	*ft_strtrim_nl(char *str)
{
	int	start;
	int	end;
	
	start = 0;
	while (str[start] == ' ' || str[start] == '\t')
		start++;
	end = ft_strlen(str) - 1;
	while (end >= start && (str[end] == '\n' || str[end] == ' '
		|| str[end] == '\r' || str[end] == '\t'))
		end--;
	if (end < start)
		return (ft_strdup(""));
	return (ft_substr(str, start, end - start + 1));
}

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	parse_rgb(char *str)
{
	char	**split;
	int	i;
	int	r;
	int	g;
	int	b;

	split = ft_split(str, ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
	{
		if (split)
		{
			i = 0;
			while (split[i])
				free(split[i++]);
			free(split);
		}
		return (-1);
	}
	if (!is_valid_number(split[0]) || !is_valid_number(split[1])
		|| !is_valid_number(split[2]))
	{
		free(split[0]);
		free(split[1]);
		free(split[2]);
		free(split);
		return (-1);
	}
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	free(split[0]);
	free(split[1]);
	free(split[2]);
	free(split);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

static int	parse_texture(char **dest, char *line)
{
	char	*trimmed;
	
	if (*dest != NULL)
		return (printf("Error\nDuplicated texture.\n"), 1);
	trimmed = ft_strtrim_nl(line);
	if (!trimmed || trimmed[0] == '\0')
		return (printf("Error\nInvalid path of texture\n"), 1);
	*dest = trimmed;
	return (0);
}

int	parse_element(char *line, t_data *data)
{
	char	*trimmed;
	int	color;

	trimmed = ft_strtrim_nl(line);
	if (!trimmed || trimmed[0] == '\0')
		return (free(trimmed), 0);
	if (!ft_strncmp(trimmed, "NO ", 3))
		return (free(trimmed), parse_texture(&data->map.path_no, line + 3));
	if (!ft_strncmp(trimmed, "SO ", 3))
		return (free(trimmed), parse_texture(&data->map.path_so, line + 3));
	if (!ft_strncmp(trimmed, "WE ", 3))
		return (free(trimmed), parse_texture(&data->map.path_we, line + 3));
	if (!ft_strncmp(trimmed, "EA ", 3))
		return (free(trimmed), parse_texture(&data->map.path_ea, line + 3));
	if (!ft_strncmp(trimmed, "F ", 2))
	{
		if (data->has_floor_color)
			return (free(trimmed), printf("Error\nDuplicate F color\n"), 1);
		color = parse_rgb(trimmed + 2);
		if (color == -1)
			return (free(trimmed), printf("Error\nInvalid Floor color\n"), 1);
		data->floor_color = color;
		data->has_floor_color = 1;
		return (free(trimmed), 0);
	}
	if (!strncmp(trimmed, "C ", 2))
	{
		if (data->has_ceiling_color)
			return (free(trimmed), printf("Error\nDuplicate C color\n"), 1);
		color = parse_rgb(trimmed + 2);
		if (color == -1)
			return (free(trimmed), printf("Error\nInvalid Cealing color\n"), 1);
		data->ceiling_color = color;
		data->has_ceiling_color = 1;
		return (free(trimmed), 0);
	}
	free(trimmed);
	return (2); //return for invalid input, A element not non
}
