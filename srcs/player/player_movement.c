/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 23:43:47 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/04/17 13:09:30 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_rotate_left(t_player *player)
{
	player->angle -= ROTATE_SIZE;
	if (player->angle < 0)
		player->angle += 2 * PI;
	player->delta_x = cos(player->angle) * STEP_SIZE;
	player->delta_y = sin(player->angle) * STEP_SIZE;
}

void	player_rotate_right(t_player *player)
{
	player->angle += ROTATE_SIZE;
	if (player->angle > 2 * PI)
		player->angle -= 2 * PI;
	player->delta_x = cos(player->angle) * STEP_SIZE;
	player->delta_y = sin(player->angle) * STEP_SIZE;
}

void	player_move_forward(t_player *player)
{
	player->x += player->delta_x;
	player->y += player->delta_y;
}

void	player_move_backward(t_player *player)
{
	player->x -= player->delta_x;
	player->y -= player->delta_y;
}