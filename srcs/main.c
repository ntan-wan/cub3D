/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 08:00:23 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/04/16 14:41:57 by ntan-wan         ###   ########.fr       */
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

t_game	*game_init(char *path_to_map)
{
	t_game		*game;
	t_map		*map;
	// t_player	*player;

	map = map_init(map_list_init(path_to_map));
	if (map)
	{
		game = malloc(sizeof(t_game));
		game->mlx = minilibx_init();
		game->map = map;
		// player = malloc(sizeof(t_player));
		// game->player = ft_memcpy(player, map->player, sizeof(t_player));
		// game->player = map->player;
	}
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

int	main(int ac , char **av)
{
	// t_game	*game;

	// game = game_init();
	// game->player = player_init(2 * CELL_SIZE, 2 * CELL_SIZE);
	// game->map = map_init(map_list_init(av[1]));
	// mlx_loop_hook(game->mlx->mlx_ptr, render, game);
	// mlx_hook(game->mlx->win_ptr, KEYPRESS, MASK_KEYPRESS, handle_keypress, game);
	// // mlx_hook(game->mlx->win_ptr, KEYRELEASE, MASK_KEYRELEASE, handle_keypress, game);
	// mlx_loop(game->mlx->mlx_ptr);
	// game_free(&game);
	// return (0);

	// render_mini_map(map_init(map_list_init("maps/map_basic.ber")));
	// map_list_init("maps/map_basic.cub");

	// t_map *map;
	// map = map_init(map_list_init(av[1]));
	// t_player p = map_player_init(map_list_init(av[1]));
	// printf("%f\n", p.x);
	// printf("%f\n", p.y);

	t_game	*game;

	game = game_init(av[1]);
	mlx_loop_hook(game->mlx->mlx_ptr, render, game);
	mlx_hook(game->mlx->win_ptr, KEYPRESS, MASK_KEYPRESS, handle_keypress, game);
	mlx_loop(game->mlx->mlx_ptr);
	game_free(&game);
	return (0);
}
