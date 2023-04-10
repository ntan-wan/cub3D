// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   render_utils.c                                     :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/03/26 20:48:13 by ntan-wan          #+#    #+#             */
// /*   Updated: 2023/04/03 17:31:11 by ntan-wan         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "cub3d.h"

// void	img_pixel_put(int x, int y, int color, t_img *img)
// {
// 	int		i;
// 	char	*pixel;	

// 	i = img->bpp - 8;
// 	pixel = img->addr + (y * img->size_line + x * (img->bpp / 8));
// 	while (i >= 0)
// 	{
// 		if (img->endian != 0)
// 			*pixel++ = (color >> i) & 0xFF;
// 		else
// 			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
// 		i -= 8;
// 	}
// }

// t_square	*sq_init(double x, double y, int width, int height, int color)
// {
// 	t_square	*sq;

// 	sq = malloc(sizeof(t_square));
// 	if (sq)
// 	{
// 		sq->x = x;
// 		sq->y = y;
// 		sq->width = width;
// 		sq->height = height;
// 		sq->color = color;
// 	}
// 	return (sq);
// }

// int	render_square(t_square *sq, t_img *buffer)
// {
// 	double	x;
// 	double	y;

// 	y = sq->y;
// 	while (y < sq->y + sq->height)
// 	{
// 		x = sq->x;
// 		while (x < sq->x + sq->width)
// 		{
// 			img_pixel_put(x, y, sq->color, buffer);
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (SUCCESS);
// }

// void	render_object_square(int x, int y, int color, t_img *buffer)
// {
// 	t_square	*sq;

// 	sq = sq_init(x, y, CELL_SIZE - 4, CELL_SIZE - 4, color);
// 	render_square(sq, buffer);
// 	free(sq);
// }

// t_triangle	*tri_init(double x, double y, int width, int height, int color)
// {
// 	t_triangle	*tri;

// 	tri = malloc(sizeof(t_triangle));
// 	if (tri)
// 	{
// 		tri->x = x;
// 		tri->y = y;
// 		tri->width = width;
// 		tri->height = height;
// 		tri->color = color;
// 	}
// 	return (tri);
// }

// int	render_triangle(t_triangle *tri, t_img *buffer)
// {
// 	double	x;
// 	double	y;
// 	int		i;
// 	double	start;

// 	i = 0;
// 	y = tri->y;
// 	while (y < tri->y + tri->height)
// 	{
// 		x = tri->x + (tri->width / 2) - i;
// 		start = x;
// 		while (x <= start + (2 * i))
// 		{
// 			img_pixel_put(x, y, tri->color, buffer);
// 			x++;
// 		}
// 		y++;
// 		i++;
// 	}
// 	return (SUCCESS);
// }

// void	render_object_triangle(int x, int y, int color, t_img *buffer)
// {
// 	t_triangle	*tri;	

// 	tri = tri_init(x, y, CELL_SIZE - 4, CELL_SIZE - 4, color);
// 	render_triangle(tri, buffer);
// 	free(tri);
// }

// void	render_player_square(t_player *player, int color, t_img *buffer)
// {
// 	double	x;
// 	double	y;

// 	x = player->x;
// 	y = player->y;
// 	render_object_square(x, y, color, buffer);
// }

// void	render_straight_line(int x1, int y1, int x2, int y2, int color, t_img *img)
// {
// 	// int	distant_x;
// 	// int	distant_y;
// 	// int	decision_param;

// 	// distant_x = x2 - x1;
// 	// distant_y = y2 - y1;
// 	// decision_param = 2 * distant_y - distant_x;
// 	// while (x1 <= x2)
// 	// {
// 	// 	img_pixel_put(x1, y1, RED, img);
// 	// 	x1++;
// 	// 	if (decision_param < 0)
// 	// 		decision_param += (2 * distant_y);
// 	// 	else
// 	// 	{
// 	// 		decision_param += (2 * distant_y) - (2 * distant_x);
// 	// 		y1++;
// 	// 	}
// 	// }

//  	double dx = abs(x2 - x1);
//     double dy = abs(y2 - y1);
//     double sx = x1 < x2 ? 1 : -1;
//     double sy = y1 < y2 ? 1 : -1;
//     double err = (dx > dy ? dx : -dy) / 2;
//     double e2;

//     while (1) {
// 		//
// 		img_pixel_put(x1, y1, color, img);
//         if (x1 == x2 && y1 == y2) {
//             break;
//         }
//         e2 = err;
//         if (e2 > -dx) {
//             err -= dy;
//             x1 += sx;
// 			// x1 += 0.1;
//         }
//         if (e2 < dy) {
//             err += dx;
//             y1 += sy;
// 			// y1 += 0.1;
//         }
//     }
// }

// void	render_square_wall(t_wall *wall, int color, t_img *buffer)
// {
// 	int	x;
// 	int	y;

// 	x = wall->x;
// 	y = wall->y;
// 	render_object_square(x, y, color, buffer);
// }

// void	render_player_direction(t_player *player, int color, t_img *buffer)
// {
// 	double	x;
// 	double	y;

// 	x = player->x + player->delta_x * 5;
// 	y = player->y + player->delta_y * 5;
// 	render_straight_line(player->x, player->y, x, y, RED, buffer);
// 	// render_object_square(x, y, color, buffer);
// }

// void	render_minimap_background(int color, t_img *buffer)
// {
// 	int	x;
// 	int	y;

// 	y = -1;
// 	while (++y < W_HEIGHT)
// 	{
// 		x = -1;
// 		while (++x < W_WIDTH)
// 			img_pixel_put(x, y, color, buffer);
// 	}
// }

// int	map_width = 10;
// int	map_height = 10;
// int map[] = {
// 	1,1,1,1,1,1,1,1,1,1,
// 	1,0,0,0,0,0,0,0,0,1,
// 	1,0,0,0,0,0,0,0,0,1,
// 	1,0,0,0,0,0,0,0,0,1,
// 	1,0,0,0,0,0,0,0,0,1,
// 	1,0,0,0,0,1,0,0,1,1,
// 	1,0,0,0,0,0,0,0,0,1,
// 	1,0,0,0,0,0,0,0,0,1,
// 	1,0,0,0,0,0,0,0,0,1,
// 	1,1,1,1,1,1,1,1,1,1,
// };

// int	find_map_cell(int x, int y)
// {
// 	return (y * map_height) + x;
// }

// void	render_blocks(t_img *buffer)
// {
// 	int		x;
// 	int		y;
	
// 	y = -1;
// 	while (++y < map_height)
// 	{
// 		x = -1;
// 		while (++x < map_width)
// 		{
// 			if (map[find_map_cell(x, y)] == 1)
// 				render_object_square(x * CELL_SIZE, y * CELL_SIZE, WHITE, buffer);
// 			else
// 				render_object_square(x * CELL_SIZE, y * CELL_SIZE, BLACK, buffer);
// 		}
// 	}
	
// }

// t_img	*img_init(void *img_ptr)
// {
// 	t_img	*img;

// 	img = ft_calloc(1, sizeof(t_img));
// 	if (img)
// 	{
// 		img ->img_ptr = img_ptr;
// 		img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_line, &img->endian);
// 	}
// 	return (img);
// }

// void	img_free(t_img **image)
// {
// 	t_img	*img;

// 	img = *image;
// 	free(img);
// 	*image = NULL;
// }

// #define mapX 10
// #define mapY 10
// #define P2 PI/2
// #define P3 3*PI/2

// double deg_to_rad(int angle)
// {
// 	return (angle * PI / 180.0);
// }

// double	dist(double ax, double ay, double bx, double by, double ang)
// {
// 	return (sqrt((bx-ax) * (bx -ax) + (by-ay) * (by-ay))); 
// }

// void	render_ray(t_player *player, t_img *buffer)
// {
// 	int r, mx, my, mp, dof;
// 	double rx, ry, ra, xo, yo;
// 	ra = player->angle;
// 	for (r = 0; r < 1; r++)
// 	{
// 		// horizontal
// 		dof = 0;
// 		double aTan = -1/tan(ra);
// 	double disH = 10000000, hx=player->x, hy = player->y;
// 		if (ra > PI)
// 		{
// 			ry = (((int)player->y >>6) << 6) - 0.0001;
// 			rx = (player->y - ry) * aTan + player->x;
// 			yo = -64;
// 			xo = -yo * aTan;
// 		}
// 		if (ra < PI)
// 		{
// 			ry = (((int)player->y >>6) << 6) +64;
// 			rx = (player->y - ry) * aTan+ player->x;
// 			yo = 64;
// 			xo = -yo * aTan;
// 		}
// 		if (ra == 0 || ra == PI)
// 		{
// 			rx = player->x;
// 			ry = player->y;
// 			dof = 8;
// 		}
// 		while (dof < 8)
// 		{
// 			mx = (int)(rx) >> 6;
// 			my = (int)(ry) >> 6;
// 			mp = my * mapX+mx;
// 			if (mp > 0 && mp < mapX * mapY && map[mp] == 1)
// 			{
// 				hx=rx; hy = ry; disH=dist(player->x, player->y, hx, hy, ra);
// 				dof=8;
// 			}
// 			else
// 			{
// 				rx+=xo;
// 				ry+=yo;
// 				dof +=1;
// 			}
// 		}
// //vertical;
// 		dof = 0;
// 		double disV=10000000, vx=player->x, vy= player->y;
// 		double nTan = -tan(ra);
// 		if (ra > P2 && ra< P3)
// 		{
// 			rx = (((int)player->x >>6) << 6) -0.0001;
// 			ry = (player->x - rx) * nTan + player->y;
// 			xo = -64;
// 			yo = -xo * nTan;
// 		}
// 		if (ra < P2 || ra > P3)
// 		{
// 			rx = (((int)player->x >>6) << 6)+64;
// 			ry = (player->x - rx) * nTan+ player->y;
// 			xo = 64;
// 			yo = -xo * nTan;
// 		}
// 		if (ra == 0 || ra == PI)
// 		{
// 			rx = player->x;
// 			ry = player->y;
// 			dof = 8;
// 		}
// 		while (dof < 8)
// 		{
// 			mx = (int)(rx) >> 6;
// 			my = (int)(ry) >> 6;
// 			mp = my * mapX+mx;
// 			if (mp > 0 && mp<mapX * mapY && map[mp] == 1)
// 			{
// 				vx=rx; vy = ry; disV=dist(player->x, player->y, vx, vy, ra);
// 				dof=8;
// 			}
// 			else
// 			{
// 				rx+=xo;
// 				ry+=yo;
// 				dof +=1;
// 			}
// 		}
// 		if (disV < disH)
// 			rx=vx; ry=vy;
// 		if (disH < disV)
// 			rx=hx;ry=hy;
// 	render_straight_line(player->x, player->y, rx, ry, GREEN, buffer);
// 	}
// }

// int	render(t_game *game)
// {
// 	t_img	*buffer;

// 	if (!game->mlx->win_ptr)
// 		return (ERROR);
// 	buffer = img_init(mlx_new_image(game->mlx->mlx_ptr, W_WIDTH, W_HEIGHT));

// 	//render things...
// 	render_minimap_background(GRAY, buffer);
// 	render_blocks(buffer);
// 	render_player_square(game->player, YELLOW, buffer);
// 	render_player_direction(game->player, BLUE, buffer);
// 	render_ray(game->player, buffer);

// 	// free resources...
// 	mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->win_ptr, buffer->img_ptr, 0, 0);
// 	mlx_destroy_image(game->mlx->mlx_ptr, buffer->img_ptr);
// 	img_free(&buffer);
// 	return (SUCCESS);
// }