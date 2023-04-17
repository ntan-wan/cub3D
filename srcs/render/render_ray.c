/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 14:45:37 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/04/18 07:09:33 by ntan-wan         ###   ########.fr       */
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

double	dist(double ax, double ay, double bx, double by, double ang)
{
	return (sqrt((bx-ax) * (bx -ax) + (by-ay) * (by-ay))); 
}

double	dist2(double start[2], double end[2], double angle)
{
	double	x_square;
	double	y_square;

	x_square = pow(end[0] - start[0], 2);
	y_square = pow(end[1] - start[1], 2);

	return (sqrt(x_square + y_square));
	// return (sqrt((bx-ax) * (bx -ax) + (by-ay) * (by-ay))); 
}

#define RAY_COUNT 64

// Depth_Of_Field
#define DOF 8

bool	is_out_of_bounds_map(int mx, int my, t_map *map)
{
	// printf("%d\n", map->width);
	// printf("%d\n", map->height);
	return (mx < 0 || mx >= map->width || my < 0 || my >= map->height);
}

bool	wall_detected(t_ray *ray, t_map *map)
{
	int		mx;
	int		my;
	int		y;
	t_list	*map_list;

	y = -1;
	mx = (int)(ray->end[0]) >> 6;
	my = (int)(ray->end[1]) >> 6;
	map_list = map->list;
	if (is_out_of_bounds_map(mx, my, map))
		return (false);
	while (map_list)
	{
		++y;
		if (y == my)
			return (((char *)map_list->content)[mx] == '1');
		map_list = map_list->next;
	}
}

double	ray_angle_adjust(double ray_angle)
{
	double	angle;

	angle = ray_angle;
	if (ray_angle < 0)
		angle += 2 * PI;
	else if (angle > 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

void	handle_ray_horizontal_up(t_ray	*ray, t_player *p)
{
	double	arc_tan;

	arc_tan = -1/tan(ray->angle);
	ray->end[1] = (((int)p->y >>6) << 6) - 0.0001;
	ray->end[0] = (p->y - ray->end[1]) * arc_tan + p->x;
	ray->y_offset = -64;
	ray->x_offset = -ray->y_offset * arc_tan;
}

void	handle_ray_horizontal_down(t_ray *ray, t_player *p)
{
	double	arc_tan;

	arc_tan = -1/tan(ray->angle);
	ray->end[1] = (((int)p->y >> 6) << 6) + 64;
	ray->end[0] = (p->y - ray->end[1]) * arc_tan + p->x;
	ray->y_offset = 64;
	ray->x_offset = -ray->y_offset * arc_tan;
}

void	handle_ray_parallel(t_ray *ray, t_player *p)
{
	ray->end[0] = p->x;
	ray->end[1] = p->y;
}

double	get_ray_len(t_ray *ray, t_map *map)
{
	double	length;
	int		depth_of_field;

	length = DBL_MAX;
	depth_of_field = 0;
	while (depth_of_field < DOF)
	{
		if (ray->angle == 0 || ray->angle == PI)
			break ;
		else if (wall_detected(ray, map))
		{
			length = dist(map->player->x, map->player->y, ray->end[0], ray->end[1], ray->angle);
			// lengh = dist2();
			break ;
		}
		else
		{
			ray->end[0] += ray->x_offset;
			ray->end[1] += ray->y_offset;
			depth_of_field++;
		}
	}
	return (length);
}

void	handle_ray_vertical_left(t_ray *ray, t_player *p)
{
	double	n_tan;

	n_tan = -tan(ray->angle);
	ray->end[0] = (((int)p->x >> 6) << 6) - 0.0001;
	ray->end[1] = (p->x - ray->end[0]) * n_tan + p->y;
	ray->x_offset = -64;
	ray->y_offset = -ray->x_offset * n_tan;
}

void	handle_ray_vertical_right(t_ray *ray, t_player *p)
{
	double	n_tan;

	n_tan = -tan(ray->angle);
	ray->end[0] = (((int)p->x >> 6) << 6) + 64;
	ray->end[1] = (p->x - ray->end[0]) * n_tan + p->y;
	ray->x_offset = 64;
	ray->y_offset = -ray->x_offset * n_tan;
}

void	double_arr_to_int_arr(double double_arr[], int int_arr[], int size)
{
	int	i;

	i = -1;
	while (++i < size)
		int_arr[i] = (int)double_arr[i];
}

void	render_ray(t_ray *ray, t_img *dst_img)
{
	t_line	*line;
	int		start[2];
	int		end[2];

	double_arr_to_int_arr(ray->start, start, 2);
	double_arr_to_int_arr(ray->end, end, 2);
	line = line_init(start, end, ray->color);
	render_line(line, dst_img);
	free(line);
}

t_ray	*ray_horizontal_init(double ray_angle, int color, t_map *map)
{
	t_player	*p;
	t_ray		*ray;

	p = map->player;
	ray = malloc(sizeof(t_ray));
	ray->color = color;
	ray->angle = ray_angle;
	ft_memcpy(ray->start, (double [2]){p->x, p->y}, sizeof(ray->start));
	if (ray_angle > PI)
		handle_ray_horizontal_up(ray, p);
	else if (ray_angle < PI)
		handle_ray_horizontal_down(ray, p);
	else if (ray_angle == 0 || ray_angle == PI)
		handle_ray_parallel(ray, p);
	ray->length = get_ray_len(ray, map);
	return (ray);
}

t_ray	*ray_vertical_init(double ray_angle, int color, t_map *map)
{
	t_player	*p;
	t_ray		*ray;
	
	p = map->player;
	ray = malloc(sizeof(t_ray));
	ray->color = color;
	ray->angle = ray_angle;
	ft_memcpy(ray->start, (double [2]){p->x, p->y}, sizeof(ray->start));
	if (ray_angle > P2 && ray_angle < P3)
		handle_ray_vertical_left(ray, p);
	else if (ray_angle < P2 || ray_angle > P3)
		handle_ray_vertical_right(ray, p);
	else if (ray_angle == 0 || ray_angle == PI)
		handle_ray_parallel(ray, p);
	ray->length = get_ray_len(ray, map);
	return (ray);
}

void	render_rays(t_map *map, t_img *buffer)
{
	t_ray		*ray_h;
	t_ray		*ray_v;
	double		ray_angle;
	int			ray_count;
	
	ray_count = -1;
	ray_angle = map->player->angle - DEG * 30;
	while (++ray_count < RAY_COUNT)
	{
		ray_angle = ray_angle_adjust(ray_angle);
		ray_h = ray_horizontal_init(ray_angle, GREEN, map);
		ray_v = ray_vertical_init(ray_angle, RED, map);
		if (ray_v->length < ray_h->length)
			render_ray(ray_v, buffer);
		else
			render_ray(ray_h, buffer);
		free(ray_h);
		free(ray_v);

	// int testx = 0;
	// int	testy = 0;
		// draw 3d wall
		// float ca = player->angle - ra; // rule of cosine , cosine angle
		// if (ca < 0)
		// 	ca += 2 * PI;
		// if (ca > 2 * PI)
		// 	ca -= 2 * PI;
		// disT = disT * cos(ca); // fix fisheye
		// float lineH = (map_width * map_height * 640) / disT; // line height
		// if (lineH > 640)
		// 	lineH = 640;
		// float line_offset = (640 - lineH) / 2;
		// // printf("line_offset %f\n", line_offset);
		// int	*start;
		// int	*end;

		// start = coord_init(testx * 10, line_offset);
		// end = coord_init(testx * 10, line_offset + lineH);
		// t_line	*line = line_init(start, end, color);
		// // render_line3(testx * 10, line_offset, testx * 10, line_offset + lineH, color, buffer);
		// render_line(line, buffer);
		// free(line);
		// free(start);
		// free(end);
		// // render_line(testx, line_offset, testx, line_offset + lineH, color, buffer);
		// // render_thick_line(testx * 10, line_offset, line_offset + lineH, 10, color, buffer);
		// // render_line(testx * 10, line_offset, testx * 10, lineH  + line_offset, color, buffer);
		// testx++;
		//
		ray_angle += DEG;
	}
}

// void    render_ray(t_map *map, t_img *dst_img)
// {
	
// }

void	render_rayzzz(t_player *player, t_img *buffer)
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
			// if (ra == 0 || ra == PI)
				// break ;
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * map_width+mx;
			// if (mx >= 0 && mx <= 9 && my >= 0 && my <= 9 && map[my][mx] == '1')
			// if (mp < mapX * mapY && map[my][mx] == '1')
			if ( mx >= 0 && my >= 0 && mx < map_width && my < map_height && map[my][mx] == '1')
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
			mp = my * map_width + mx;
			
			if ( mx >= 0 && my >= 0 && mx < map_width && my < map_height && map[my][mx] == '1')
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