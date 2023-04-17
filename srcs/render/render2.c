/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 22:01:20 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/04/18 06:21:02 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	render_mini_player_next_move(t_player *player, int color, t_img *img)
// {
// 	int	x;
// 	int	y;

// 	x = player->x + player->delta_x;
// 	y = player->y + player->delta_y;
// 	// render_line(player->x, player->y, x, y, RED, img);
// 	render_block(x, y, CELL_SIZE - 4, CELL_SIZE - 4, color, img);
// }


int	*coord_init(int x, int y)
{
	int	*coord;

	coord = malloc(2 * sizeof(int));
	if (coord)
	{
		coord[0] = x;
		coord[1] = y;
	}
	return (coord);
}

// img utils
t_img	*img_init(void *img_ptr)
{
	t_img	*img;

	img = ft_calloc(1, sizeof(t_img));
	if (img)
	{
		img ->img_ptr = img_ptr;
		img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_line, &img->endian);
	}
	return (img);
}

void	img_free(t_img **image)
{
	t_img	*img;

	img = *image;
	free(img);
	*image = NULL;
}

int	is_pixel_black(char *pixel)
{
	return (*pixel == 0);
}

void	sl_copy_pixel(char *dst, char *src, int bytes_per_pixel)
{
	int	i;

	i = -1;
	if (dst && src)
	{
		while (++i < bytes_per_pixel)
			dst[i] = src[i];
	}
	else
		ft_printf("copy_pixel: src or dst not found\n");
}

/* 
	Eg: coordinate = (0, -1), img = 4 x 4 resolution.
	Should copy 4 columns and 3 rows only as the first 
	row is out of boundary.Hence, start to copy from 
	0th(index) column and 1st(index) row. 
	Else, copy the whole img.
 */
int	sl_copy_starting_pixel(int num)
{
	if (num < 0)
		num = -num;
	else
		num = -1;
	return (num);
}

/*
	s = sources
	d = destination
	x and y = dst's coordinate
 */
void	sl_copy_img(t_img *dst, t_img *src, int x, int y)
{
	int			i;
	int			j;
	t_img		s;
	t_img		d;
	char		*s_pixel;
	char		*d_pixel;

	if (!src || !dst)
	{
		ft_printf("copy_img: src or dst not found\n");
		return ;
	}
	s.addr = mlx_get_data_addr(src->img_ptr, &s.bpp, &s.size_line, &s.endian);
	d.addr = mlx_get_data_addr(dst->img_ptr, &d.bpp, &d.size_line, &d.endian);
	i = sl_copy_starting_pixel(y);
	while (++i < src->height && y + i < dst->height)
	{
		j = sl_copy_starting_pixel(x);
		while (++j < src->width && x + j < dst->width)
		{
			s_pixel = s.addr + ((i * s.size_line) + (j * (s.bpp / 8)));
			d_pixel = d.addr + ((i + y) * d.size_line + (j + x) * (d.bpp / 8));
			if (!is_pixel_black(s_pixel))
				sl_copy_pixel(d_pixel, s_pixel, 4);
		}
	}
}


// render
int	render(t_game *game)
{
	t_img	*img;

	if (!game->mlx->win_ptr)
		return (ERROR);
	img = img_init(mlx_new_image(game->mlx->mlx_ptr, W_WIDTH, W_HEIGHT));

	//render things...
	// render_background(GRAY, img);
	// render_mini_map(img);
	// render_mini_player(game->player, YELLOW, img);
	// render_mini_player_next_move(game->player, TEAL, img);
	// render_rayzzz(game->map->player, img);

	render_rays(game->map, img);
	render_mini_map(game->map, img);
	// render_mini_player(game->map->player, YELLOW, img);
	
	// t_block	b;
	// b.height = CELL_SIZE;
	// b.width = CELL_SIZE;
	// b.color = RED;
	// b.coord[0] = 1 * CELL_SIZE;
	// b.coord[1] = 1 * CELL_SIZE;
	// render_block(&b, img);

	// t_line line;
	// line.color = RED;
	// line.start[0] = 0;
	// line.start[1] = 0;
	// line.end[0] = 5 * CELL_SIZE;
	// line.end[1] = 5 * CELL_SIZE;
	// line.delta_x = abs(line.end[0] - line.start[0]);
	// line.delta_y = abs(line.end[1] - line.start[1]);
	// render_line(&line, img);

	//put image to window...
	mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->win_ptr, img->img_ptr, 0, 0);

	// free resources...
	mlx_destroy_image(game->mlx->mlx_ptr, img->img_ptr);
	img_free(&img);
	return (SUCCESS);
}