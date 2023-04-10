/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 22:01:20 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/04/10 18:02:21 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
int	sl_copy_starting_pixel(int num);

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

void	img_pixel_put(int x, int y, int color, t_img *img)
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

void	render_square(int x, int y, int width, int height, int color, t_img *img)
{
	int	coord_x;
	int	coord_y;

	coord_x = x;
	coord_y = y;
	while (coord_y < y + height)
	{
		coord_x = x;
		while (coord_x < x + width)
		{
			img_pixel_put(coord_x, coord_y, color, img);
			coord_x++;
		}
		coord_y++;
	}
}

void	render_minimap_background(int color, t_img *img)
{
	int	x;
	int	y;

	y = -1;
	while (++y < W_HEIGHT)
	{
		x = -1;
		while (++x < W_WIDTH)
			img_pixel_put(x, y, color, img);
	}
}


int	straight_line_step_get(int start_point, int end_point)
{
	if (start_point < end_point)
		return (1);
	else
		return (-1);
}

void	render_straight_line(int x0, int y0, int x1, int y1, int color, t_img *img)
{
	int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (x0 != x1 || y0 != y1)
    {
		//
		// x0 = sl_copy_starting_pixel(x0);
		// y0 = sl_copy_starting_pixel(y0);
		//
		if (x0 < 0 || y0 < 0 || x0 > W_WIDTH || y0 > W_HEIGHT)
			break ;
		//
		img_pixel_put(x0, y0, color, img);
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void	render_mini_player_next_move(t_player *player, int color, t_img *img)
{
	int	x;
	int	y;

	x = player->x + player->delta_x;
	y = player->y + player->delta_y;
	// render_straight_line(player->x, player->y, x, y, RED, img);
	render_square(x, y, CELL_SIZE - 4, CELL_SIZE - 4, color, img);
}

#define P2 PI/2
#define P3 3*PI/2
#define mapX 10
#define mapY 10
#define DEG 0.0174533

double	dist(double ax, double ay, double bx, double by, double ang)
{
	return (sqrt((bx-ax) * (bx -ax) + (by-ay) * (by-ay))); 
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
			// printf("mx %d\n", mx);
			// printf("my %d\n", my);
			// printf("rx %f\n", rx);
			// printf("ry %f\n", ry);
		}
		// hx=rx; hy = ry; disH=dist(player->x, player->y, hx, hy, ra);
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
			
			// printf("mx %d\n", mx);
			// printf("my %d\n", my);
			// if (mp < mapX * mapY && map[my][mx] == '1')
			if ( mx >= 0 && my >= 0 && mx < mapX && my < mapY && map[my][mx] == '1')
			{
				vx=rx; vy = ry; disV=dist(player->x, player->y, vx, vy, ra);
				// dof=8;
				break ;
			}
			else
			{
				rx+=xo;
				ry+=yo;
				dof +=1;
			}
			// printf("rx %f\n", rx);
			// printf("ry %f\n", ry);
		}
		
		int	color;

		if (disV < disH)
		{
			rx=vx;
			ry=vy;
			disT = disV;
			// color = encode_rgb(0.9, 0, 0);
			color = encode_rgb(0, 250, 0);
		}
		else if (disH < disV)
		{
			rx=hx;
			ry=hy;
			disT = disH;
			color = encode_rgb(0, 100, 0);
		}
		// render_straight_line(player->x, player->y, rx, ry, RED, buffer);

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
		// float line_offset = 640 - (lineH / 2);
		float line_offset = (640 - lineH) / 2;
		// printf("line_offset %f\n", line_offset);
		render_straight_line(testx * 10, line_offset, testx * 10, line_offset + lineH, color, buffer);
		// render_straight_line(testx * 10, line_offset, testx * 10, lineH  + line_offset, color, buffer);
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


void	render_mini_player(t_player *p, int color, t_img *img)
{
	// render_square((W_WIDTH - CELL_SIZE) / 2, (W_HEIGHT - CELL_SIZE)  / 2, CELL_SIZE - 4, CELL_SIZE - 4, color, img);
	render_square(p->x, p->y, CELL_SIZE - 4, CELL_SIZE - 4, color, img);
}

void	render_minimap(t_img *img)
{
	int	x;
	int	y;
	
	y = -1;
	while (++y < map_height)
	{
		x = -1;
		while (++x < map_width)
		{
			if (map[y][x] == '1')
				render_square(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE - 4, CELL_SIZE - 4, WHITE, img);
			else
				render_square(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE - 4, CELL_SIZE - 4, BLACK, img);
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
	// render_minimap_background(GRAY, img);
	// render_minimap(img);
	// render_mini_player(game->player, YELLOW, img);
	// render_mini_player_next_move(game->player, TEAL, img);
	render_ray(game->player, img);

	//put image to window...
	mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->win_ptr, img->img_ptr, 0, 0);

	// free resources...
	mlx_destroy_image(game->mlx->mlx_ptr, img->img_ptr);
	img_free(&img);
	return (SUCCESS);
}