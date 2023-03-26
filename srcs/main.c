/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 08:00:23 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/26 18:33:20 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red <<16 | green << 8 | blue);
}

void	img_pixel_put(t_img *img, int x, int y, int color)
{
	int		i;
	char	*pixel;	

	i = img->bpp - 8;
	pixel = img->addr + (y * img->size_line + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	algo_bresenham(t_img *img, int x1, int y1, int x2, int y2)
{
	int	distant_x;
	int	distant_y;
	int	decision_param;

	distant_x = x2 - x1;
	distant_y = y2 - y1;
	decision_param = 2 * distant_y - distant_x;
	while (x1 <= x2)
	{
		// img_pixel_put(x1, y1)...
		img_pixel_put(img , x1, y1, 0xFF0000);
		x1++;
		if (decision_param < 0)
			decision_param += (2 * distant_y);
		else
		{
			decision_param += (2 * distant_y) - (2 * distant_x);
			y1++;
		}
	}
}

/* render*/

int	render_square(t_square *sq, t_img *buffer_img)
{
	int	x;
	int	y;

	y = sq->y;
	while (y < sq->y + sq->height)
	{
		x = sq->x;
		while (x < sq->x + sq->width)
		{
			img_pixel_put(buffer_img, x, y, sq->color);
			x++;
		}
		y++;
	}
	return (SUCCESS);
}

t_square	*sq_init(int x, int y, int width, int height, int color)
{
	t_square	*sq;

	sq = malloc(sizeof(t_square));
	if (sq)
	{
		sq->x = x;
		sq->y = y;
		sq->width = width;
		sq->height = height;
		sq->color = color;
	}
	return (sq);
}

void	render_square_player(t_player *player, t_img *buffer_img)
{
	t_square	*sq;

	sq = sq_init(player->x, player->y, PIXEL_SIZE - 4, PIXEL_SIZE - 4, YELLOW);
	// sq = sq_init(player->x + player->delta_x * 5, player->y + player->delta_y * 5, PIXEL_SIZE - 4, PIXEL_SIZE - 4, YELLOW);
	render_square(sq, buffer_img);
	free(sq);
}

void	render_square_wall(t_wall *wall, int color, t_img *buffer_img)
{
	t_square	*sq;
	sq = sq_init(wall->x, wall->y, PIXEL_SIZE - 4, PIXEL_SIZE - 4, color);
	render_square(sq, buffer_img);
	free(sq);
}

void	render_wall(t_img *buffer_img)
{
	int		x;
	int		y;
	t_wall	wall;
	int	arr[10][10] = {
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1},
	};

	y = -1;
	while (++y < 10)
	{
		x = -1;
		while (++x < 10)
		{
			wall.x = x * PIXEL_SIZE;
			wall.y = y * PIXEL_SIZE;
			if (arr[y][x] == 1)
				render_square_wall(&wall, WHITE, buffer_img);
			else
				render_square_wall(&wall, BLACK, buffer_img);
		}
	}
	
}

void	render_background(int color, t_img *buffer_img)
{
	int	x;
	int	y;

	y = -1;
	while (++y < W_HEIGHT)
	{
		x = -1;
		while (++x < W_WIDTH)
			img_pixel_put(buffer_img, x, y, color);
	}
}

void	render_player_direction(t_player *player, t_img *buffer_img)
{
	t_square	*sq;
	
	sq = sq_init(player->x + player->direction.delta_x * 5, player->y + player->direction.delta_y * 5, PIXEL_SIZE - 4, PIXEL_SIZE - 4, BLUE);
	render_square(sq, buffer_img);
}

int	render(t_game *game)
{
	t_img	buffer_img;

	if (!game->mlx->win_ptr)
		return (ERROR);
	buffer_img.img_ptr = mlx_new_image(game->mlx->mlx_ptr, W_WIDTH, W_HEIGHT);
	buffer_img.addr = mlx_get_data_addr(buffer_img.img_ptr, &buffer_img.bpp, &buffer_img.size_line, &buffer_img.endian);
	//render things...
	render_background(GRAY, &buffer_img);
	// render_minimap(&buffer_img);
	render_wall(&buffer_img);
	render_square_player(game->player, &buffer_img);
	render_player_direction(game->player, &buffer_img);
	mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->win_ptr, buffer_img.img_ptr, 0, 0);
	mlx_destroy_image(game->mlx->mlx_ptr, buffer_img.img_ptr);
	return (SUCCESS);
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
		// game->player->x += PIXEL_SIZE;

		game->player->direction.angle += 0.1;
		if (game->player->direction.angle > 2 * M_PI)
			game->player->direction.angle -= 2 * M_PI;
		game->player->direction.delta_x = cos(game->player->direction.angle) * 5;
		game->player->direction.delta_y = sin(game->player->direction.angle) * 5;
		// printf("delta x %f\n", game->player->delta_x);
		// printf("delta y %f\n", game->player->delta_y);
	}
	else if (keycode == KEY_A)
	{
		// game->player->x -= PIXEL_SIZE;
		game->player->direction.angle -= 0.1;
		if (game->player->direction.angle < 0)
			game->player->direction.angle += 2 * M_PI;
		game->player->direction.delta_x = cos(game->player->direction.angle) * 5;
		game->player->direction.delta_y = sin(game->player->direction.angle) * 5;
	}
	else if (keycode == KEY_W)
	{
		// game->player->y -= PIXEL_SIZE;
		game->player->x += game->player->direction.delta_x;
		game->player->y += game->player->direction.delta_y;
	}
	else if (keycode == KEY_S)
	{
		// game->player->y += PIXEL_SIZE;
		game->player->x -= game->player->direction.delta_x;
		game->player->y -= game->player->direction.delta_y;
	}
	return (SUCCESS);
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
		// p->delta_x = cos(p->angle) * 5;
		// p->delta_y = sin(p->angle) * 5;
		p->direction.delta_x = cos(p->direction.angle) * 5;
		p->direction.delta_y = sin(p->direction.angle) * 5;
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

t_game	*game_init()
{
	t_game *game;

	game = malloc(sizeof(t_game));
	if (game)
	{
		game->mlx = minilibx_init();
		// init player x and y coordinate
		game->player = player_init(1 * PIXEL_SIZE, 1 * PIXEL_SIZE);
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

	game = game_init();
	mlx_loop_hook(game->mlx->mlx_ptr, render, game);
	mlx_hook(game->mlx->win_ptr, KEYPRESS, MASK_KEYPRESS, handle_keypress, game);
	mlx_loop(game->mlx->mlx_ptr);
	game_free(&game);
	return (0);
}
