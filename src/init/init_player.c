/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 21:33:27 by kali              #+#    #+#             */
/*   Updated: 2026/04/09 21:33:30 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_player_dir(t_data *data)
{
	if (data->player.spawn_dir == 'N')
	{
		data->player.dir.x = 0.0;
		data->player.dir.y = -1.0;
		data->player.plane.x = 0.66;
		data->player.plane.y = 0.0;
	}
	else if (data->player.spawn_dir == 'S')
	{
		data->player.dir.x = 0.0;
		data->player.dir.y = 1.0;
		data->player.plane.x = -0.66;
		data->player.plane.y = 0.0;
	}
	else if (data->player.spawn_dir == 'W')
	{
		data->player.dir.x = -1.0;
		data->player.dir.y = 0.0;
		data->player.plane.x = 0.0;
		data->player.plane.y = -0.66;
	}
	else if (data->player.spawn_dir == 'E')
	{
		data->player.dir.x = 1.0;
		data->player.dir.y = 0.0;
		data->player.plane.x = 0.0;
		data->player.plane.y = 0.66;
	}
}
