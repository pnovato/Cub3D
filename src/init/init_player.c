/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 21:33:27 by kali              #+#    #+#             */
/*   Updated: 2026/05/04 06:58:13 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_player_dir(t_data *data)
{
	t_player	*p;

	p = &data->player;
	p->dir.x = (p->spawn_dir == 'E') - (p->spawn_dir == 'W');
	p->dir.y = (p->spawn_dir == 'S') - (p->spawn_dir == 'N');
	p->plane.x = ((p->spawn_dir == 'N') - (p->spawn_dir == 'S')) * 0.66;
	p->plane.y = ((p->spawn_dir == 'E') - (p->spawn_dir == 'W')) * 0.66;
}
