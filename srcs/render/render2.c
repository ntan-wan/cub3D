/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 22:01:20 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/04/16 14:40:28 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_width = 10;
int	map_height = 10;
char *map[] = {
	"1111111111",
	"1000000001",
	"1000000001",
	"1000000001",
	"1000000001",
	"1000000001",
	"1000001001",
	"1000010001",
	"1000000001",
	"1111111111",
};

// void	render_mini_player_next_move(t_player *player, int color, t_img *img)
// {
// 	int	x;
// 	int	y;

// 	x = player->x + player->delta_x;
// 	y = player->y + player->delta_y;
// 	// render_line(player->x, player->y, x, y, RED, img);
// 	render_block(x, y, CELL_SIZE - 4, CELL_SIZE - 4, color, img);
// }

#define P2 PI/2
#define P3 3*PI/2
#define mapX 10
#define mapY 10
#define DEG 0.0174533

double	dist(double ax, double ay, double bx, double by, double ang)
{
	return (sqrt((bx-ax) * (bx -ax) + (by-ay) * (by-ay))); 
}

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

void	render_ray(t_player *player, t_img *buffer)
{
	int r, mx, my, mp, dof, disT;
	double rx, ry, ra, xo, yo;
	//
	ra = player->angle - DEG * 30;
	// ra = player->angle;
		int testx = 0;
		int	testy = 0;
	if (ra < 0)
		ra += 2 * PI;
	if (ra > 2 * PI)
		ra -= 2 * PI;
	for (r = 0; r < 64; r++)
	{
		// horizontal
		dof = 0;
		double aTan = -1/tan(ra);
		double disH = 1000000, hx=player->x, hy = player->y;
		if (ra > PI)
		{
			ry = (((int)player->y >>6) << 6) - 0.0001;
			rx = (player->y - ry) * aTan + player->x;
			yo = -64;
			xo = -yo * aTan;
		}
		if (ra < PI)
		{
			ry = (((int)player->y >>6) << 6) +64;
			rx = (player->y - ry) * aTan+ player->x;
			yo = 64;
			xo = -yo * aTan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = player->x;
			ry = player->y;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * mapX+mx;
			// if (mx >= 0 && mx <= 9 && my >= 0 && my <= 9 && map[my][mx] == '1')
			// if (mp < mapX * mapY && map[my][mx] == '1')
			if ( mx >= 0 && my >= 0 && mx < mapX && my < mapY && map[my][mx] == '1')
			{
				hx=rx; hy = ry; disH=dist(player->x, player->y, hx, hy, ra);
				// dof=8;
				break ;
			}
			else
			{
				rx+=xo;
				ry+=yo;
				dof+=1;
			}
		}
//vertical;
		dof = 0;
		double disV=1000000, vx=player->x, vy= player->y;
		double nTan = -tan(ra);
		if (ra > P2 && ra < P3)
		{
			rx = (((int)player->x >>6) << 6) -0.0001;
			ry = (player->x - rx) * nTan + player->y;
			xo = -64;
			yo = -xo * nTan;
		}
		if (ra < P2 || ra > P3)
		{
			rx = (((int)player->x >>6) << 6)+64;
			ry = (player->x - rx) * nTan+ player->y;
			xo = 64;
			yo = -xo * nTan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = player->x;
			ry = player->y;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * mapX + mx;
			
			if ( mx >= 0 && my >= 0 && mx < mapX && my < mapY && map[my][mx] == '1')
			{
				vx=rx; vy = ry; disV=dist(player->x, player->y, vx, vy, ra);
				break ;
			}
			else
			{
				rx+=xo;
				ry+=yo;
				dof +=1;
			}
		}
		
		int	color;

		if (disV < disH)
		{
			rx=vx;
			ry=vy;
			disT = disV;
			color = pixel_encode_rgb(0, 250, 0);
		}
		else if (disH < disV)
		{
			rx=hx;
			ry=hy;
			disT = disH;
			color = pixel_encode_rgb(0, 100, 0);
		}
		int	*start0;
		int	*end0;

		start0 = coord_init(player->x, player->y);
		end0 = coord_init(rx, ry);
		t_line	*line0 = line_init(start0, end0, RED);
		render_line(line0, buffer);
		free(start0);
		free(end0);
		free(line0);

		// draw 3d wall
		float ca = player->angle - ra; // rule of cosine , cosine angle
		if (ca < 0)
			ca += 2 * PI;
		if (ca > 2 * PI)
			ca -= 2 * PI;
		disT = disT * cos(ca); // fix fisheye
		float lineH = (map_width * map_height * 640) / disT; // line height
		if (lineH > 640)
			lineH = 640;
		float line_offset = (640 - lineH) / 2;
		// printf("line_offset %f\n", line_offset);
		int	*start;
		int	*end;

		start = coord_init(testx * 10, line_offset);
		end = coord_init(testx * 10, line_offset + lineH);
		t_line	*line = line_init(start, end, color);
		// render_line3(testx * 10, line_offset, testx * 10, line_offset + lineH, color, buffer);
		render_line(line, buffer);
		free(line);
		free(start);
		free(end);
		// render_line(testx, line_offset, testx, line_offset + lineH, color, buffer);
		// render_thick_line(testx * 10, line_offset, line_offset + lineH, 10, color, buffer);
		// render_line(testx * 10, line_offset, testx * 10, lineH  + line_offset, color, buffer);
		testx++;
		//
		ra += DEG;
		if (ra < 0)
			ra += 2 * PI;
		if (ra > 2 * PI)
			ra -= 2 * PI;
	}
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


// void	render_mini_player(t_player *p, int color, t_img *dst_img)
// {
// 	// render_block((W_WIDTH - CELL_SIZE) / 2, (W_HEIGHT - CELL_SIZE)  / 2, CELL_SIZE - 4, CELL_SIZE - 4, color, img);
// 	// render_block(p->x, p->y, CELL_SIZE - 4, CELL_SIZE - 4, color, img);
// 	// render_block_object(p->x, p->y, color, dst_img);
// }



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
	// render_ray(game->map->player, img);
	// render_mini_map(game->map, img);
	render_mini_map(game->map, img);
	// render_mini_player(game->player, YELLOW, img);
	
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