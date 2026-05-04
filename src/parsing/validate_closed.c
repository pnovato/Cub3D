/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_closed.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 11:40:00 by kali              #+#    #+#             */
/*   Updated: 2026/05/04 06:42:15 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_cell(t_data *data, int i, int j)
{
	char	**m;
	int		len;

	m = data->map.map;
	if (m[i][j] != '0')
		return (0);
	len = ft_strlen(m[i]);
	if (i == 0 || !m[i + 1] || j == 0 || j >= len - 1)
		return (printf("Error\nMap is not closed\n"), 1);
	if (m[i - 1][j] == ' ' || m[i - 1][j] == '\0')
		return (printf("Error\nMap is not closed\n"), 1);
	if (m[i + 1][j] == ' ' || m[i + 1][j] == '\0')
		return (printf("Error\nMap is not closed\n"), 1);
	if (m[i][j - 1] == ' ' || m[i][j + 1] == ' ')
		return (printf("Error\nMap is not closed\n"), 1);
	if (m[i][j + 1] == '\0')
		return (printf("Error\nMap is not closed\n"), 1);
	return (0);
}

int	check_closed(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map.map[++i])
	{
		j = -1;
		while (data->map.map[i][++j])
		{
			if (check_cell(data, i, j))
				return (1);
		}
	}
	return (0);
}
