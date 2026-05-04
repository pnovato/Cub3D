/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 21:45:50 by kali              #+#    #+#             */
/*   Updated: 2026/05/04 06:42:25 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_valid_char(int c)
{
	if (c == '0' || c == '1' || c == ' ')
		return (1);
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

static int	is_player(int c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

static int	check_char(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map.map[++i])
	{
		j = -1;
		while (data->map.map[i][++j])
		{
			if (!is_valid_char(data->map.map[i][j]))
			{
				printf("Error\nInvalid map char\n");
				return (1);
			}
		}
	}
	return (0);
}

static int	find_player(t_data *data)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = -1;
	while (data->map.map[++i])
	{
		j = -1;
		while (data->map.map[i][++j])
		{
			if (is_player(data->map.map[i][j]))
			{
				count++;
				data->player.pos.x = j + 0.5;
				data->player.pos.y = i + 0.5;
				data->player.spawn_dir = data->map.map[i][j];
				data->map.map[i][j] = '0';
			}
		}
	}
	if (count != 1)
		return (printf("Error\nInvalid number of players\n"), 1);
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
