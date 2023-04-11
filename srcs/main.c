/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 08:00:23 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/04/10 23:57:29 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_mlx	*minilibx_init(void)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, W_WIDTH, W_HEIGHT, "cub3d");
	return (mlx);
}

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

t_game	*game_init()
{
	t_game *game;

	game = malloc(sizeof(t_game));
	if (game)
		game->mlx = minilibx_init();
	return (game);
}

void	game_free(t_game **game)
{
	t_game	*g;

	g = *game;
	
	minilibx_free(&g->mlx);
	free(g);
	*game = NULL;
}

int	main(void)
{
	t_game	*game;

	game = game_init();
	game->player = player_init(2, 2);
	mlx_loop_hook(game->mlx->mlx_ptr, render, game);
	mlx_hook(game->mlx->win_ptr, KEYPRESS, MASK_KEYPRESS, handle_keypress, game);
	// mlx_hook(game->mlx->win_ptr, KEYRELEASE, MASK_KEYRELEASE, handle_keypress, game);
	mlx_loop(game->mlx->mlx_ptr);
	game_free(&game);
	return (0);
}
