/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 08:00:23 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/04/10 14:34:00 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red <<16 | green << 8 | blue);
}

/* keypress handler */
int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(game->mlx->mlx_ptr, game->mlx->win_ptr);
		game->mlx->win_ptr = NULL;
	}
	else if (keycode == KEY_D)
	{
		game->player->angle += ROTATE_SIZE;
		if (game->player->angle > 2 * PI)
			game->player->angle -= 2 * PI;
		game->player->delta_x = cos(game->player->angle) * STEP_SIZE;
		game->player->delta_y = sin(game->player->angle) * STEP_SIZE;
	}
	else if (keycode == KEY_A)
	{
		game->player->angle -= ROTATE_SIZE;
		if (game->player->angle < 0)
			game->player->angle += 2 * PI;
		game->player->delta_x = cos(game->player->angle) * STEP_SIZE;
		game->player->delta_y = sin(game->player->angle) * STEP_SIZE;
	}
	else if (keycode == KEY_W)
	{
		game->player->x += game->player->delta_x;
		game->player->y += game->player->delta_y;
	}
	else if (keycode == KEY_S)
	{
		game->player->x -= game->player->delta_x;
		game->player->y -= game->player->delta_y;
	}
	return (SUCCESS);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	
}

/* init */
t_player	*player_init(int x, int y)
{
	t_player	*p;

	p = ft_calloc(1, sizeof(t_player));
	if (p)
	{
		p->x = x;
		p->y = y;
		p->delta_x = cos(p->angle) * STEP_SIZE;
		p->delta_y = sin(p->angle) * STEP_SIZE;
	}
	return (p);
}

t_mlx	*minilibx_init(void)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, W_WIDTH, W_HEIGHT, "cub3d");
	return (mlx);
}

t_game	*game_init(int p_x, int p_y)
{
	t_game *game;

	game = malloc(sizeof(t_game));
	if (game)
	{
		game->mlx = minilibx_init();
		// init player x and y coordinate
		game->player = player_init(p_x * CELL_SIZE, p_y * CELL_SIZE);
	}
	return (game);
}

/* free */
void	minilibx_free(t_mlx **minilibx)
{
	t_mlx	*mlx;

	mlx = *minilibx;
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	free(mlx->win_ptr);
	free(mlx);
	*minilibx = NULL;
}

void	player_free(t_player **player)
{
	t_player	*p;

	p = *player;
	free(p);
	*player = NULL;
}

void	game_free(t_game **game)
{
	t_game	*g;

	g = *game;
	
	minilibx_free(&g->mlx);
	player_free(&g->player);
	free(g);
	*game = NULL;
}

/* main */
int	main(void)
{
	t_game	*game;

	game = game_init(3, 4);
	mlx_loop_hook(game->mlx->mlx_ptr, render, game);
	mlx_hook(game->mlx->win_ptr, KEYPRESS, MASK_KEYPRESS, handle_keypress, game);
	// mlx_hook(game->mlx->win_ptr, KEYRELEASE, MASK_KEYRELEASE, handle_keypress, game);
	mlx_loop(game->mlx->mlx_ptr);
	game_free(&game);
	return (0);
}
