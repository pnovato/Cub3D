/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 12:00:00 by kali              #+#    #+#             */
/*   Updated: 2026/05/04 07:09:39 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
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
	char	**sp;
	int		c[3];

	sp = ft_split(str, ',');
	if (!sp || !sp[0] || !sp[1] || !sp[2] || sp[3])
		return (free_split(sp), -1);
	if (!is_valid_number(sp[0]) || !is_valid_number(sp[1])
		|| !is_valid_number(sp[2]))
		return (free_split(sp), -1);
	c[0] = ft_atoi(sp[0]);
	c[1] = ft_atoi(sp[1]);
	c[2] = ft_atoi(sp[2]);
	free_split(sp);
	if (c[0] < 0 || c[0] > 255 || c[1] < 0 || c[1] > 255
		|| c[2] < 0 || c[2] > 255)
		return (-1);
	return ((c[0] << 16) | (c[1] << 8) | c[2]);
}

int	parse_color(char *line, t_data *data, char type)
{
	int		color;
	char	*trim;

	trim = ft_strtrim(line, " \t\n\r");
	color = parse_rgb(trim + 2);
	free(trim);
	if (color == -1)
		return (printf("Error\nInvalid %c color format\n", type), 1);
	if (type == 'F')
	{
		if (data->has_floor_color)
			return (printf("Error\nDuplicate F color\n"), 1);
		data->floor_color = color;
		data->has_floor_color = 1;
	}
	else
	{
		if (data->has_ceiling_color)
			return (printf("Error\nDuplicate C color\n"), 1);
		data->ceiling_color = color;
		data->has_ceiling_color = 1;
	}
	return (0);
}
