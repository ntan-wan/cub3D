/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 23:08:13 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/04/11 12:35:37 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_button_esc(void *mlx_ptr, void **win_ptr)
{
	mlx_destroy_window(mlx_ptr, *win_ptr);
	*win_ptr = NULL;
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == ESC)
		handle_button_esc(game->mlx->mlx_ptr, &game->mlx->win_ptr);
	else if (keycode == KEY_D)
		player_rotate_right(game->player);
	else if (keycode == KEY_A)
		player_rotate_left(game->player);
	else if (keycode == KEY_W)
		player_move_forward(game->player);
	else if (keycode == KEY_S)
		player_move_backward(game->player);
	return (SUCCESS);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	
}