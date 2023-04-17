/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 14:45:37 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/04/18 05:31:04 by ntan-wan         ###   ########.fr       */
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

double	get_ray_angle(double player_angle)
{
	double	ray_angle;

	ray_angle =  player_angle - (DEG * 30);
	if (ray_angle < 0)
		ray_angle = 2 * PI;
	else if (ray_angle > 2 * PI)
		ray_angle = 0;
	return (ray_angle);
}

void	handle_ray_horizontal_up(t_ray *ray, double arc_tan, t_player *p)
{
	// double	arc_tan = -1/tan(ray->angle);

	ray->end[1] = (((int)p->y >> 6) << 6) - 0.0001;
	ray->end[0] = (p->y - ray->end[1]) * arc_tan + p->x;
	ray->y_offset = -64;
	ray->x_offset = -ray->y_offset * arc_tan;
}

void	handle_ray_horizontal_down(t_ray *ray, double arc_tan, t_player *p)
{
	// double	arc_tan = -1/tan(ray->angle);

	ray->end[1] = (((int)p->y >> 6) << 6) + 64;
	ray->end[0] = (p->y - ray->end[1]) * arc_tan + p->x;
	ray->y_offset = 64;
	ray->x_offset = -ray->y_offset * arc_tan;
}

void	handle_ray_parallel(t_ray *ray, t_player *p)
{
	ray->end[0] = p->x;
	ray->end[1] = p->y;
	//
	// dof = 8;
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


bool	test(int mx, int my, t_map *map)
{
	return ( mx >= 0 && my >= 0 && mx < map->width && my < map->height);
}

bool	wall_contact_detected(int mx, int my, t_map *map)
{
	int		y;
	t_list	*map_list;

	map_list = map->list;
	y = -1;
	// if (is_out_of_bounds_map(mx, my, map))
		// return (false);
	while (map_list)
	{
		++y;
		if (y == my)
			return (((char *)map_list->content)[mx] == '1');
		map_list = map_list->next;
	}
	// return (false);
}

double	get_ray_len(t_ray *ray, t_map *map)
{
	int		mx;
	int		my;
	double	length;
	int		depth_of_field;
	t_player	*p;

	p = map->player;
	length = DBL_MAX;
	// printf("%f\n", length);
	// length = 1000000;
	depth_of_field = 0;
	while (depth_of_field < DOF)
	{
		mx = (int)(ray->end[0]) >> 6;
		my = (int)(ray->end[1]) >> 6;
		if (ray->angle == 0 || ray->angle == PI)
			break ;
		else if (wall_contact_detected(mx, my, map))
		///
		// else if (test(mx, my, map))
		//
		{
			length = dist(p->x, p->y, ray->end[0], ray->end[1], ray->angle);
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

void	ray_horizontal_init(t_ray *ray, double ray_angle, int color, t_map *map)
{
	t_player	*p;
	double		arc_tan;

	arc_tan = -1/tan(ray_angle);
	p = map->player;
	ray->color = color;
	ray->angle = ray_angle;
	ft_memcpy(ray->start, (int [2]){p->x, p->y}, sizeof(ray->start));
	if (ray->angle > PI)
		handle_ray_horizontal_up(ray, arc_tan, p);
	if (ray->angle < PI)
		handle_ray_horizontal_down(ray, arc_tan, p);
	if (ray->angle == 0 || ray->angle == PI)
		handle_ray_parallel(ray, p);
	ray->length = get_ray_len(ray, map);
}

// void	render_ray2(t_ray *ray, t_img *dst_img)
// {
// 	t_line	*line;

// 	line = line_init(ray->start, ray->end, ray->color);
// 	render_line(line, dst_img);
// 	free(line);
// }

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

void	ray_vertical_init(t_ray *ray, double ray_angle, int color, t_map *map)
{
	t_player	*p;

	p = map->player;
	ray->color = color;
	ray->angle = ray_angle;
	ft_memcpy(ray->start, (int [2]){p->x, p->y}, sizeof(ray->start));
	if (ray->angle > P2 && ray->angle < P3)
		handle_ray_vertical_left(ray, p);
	if (ray->angle < P2 || ray->angle > P3)
		handle_ray_vertical_right(ray, p);
	if (ray->angle == 0 || ray->angle == PI)
		handle_ray_parallel(ray, p);
	ray->length = get_ray_len(ray, map);
}

double	ray_angle_adjust(double ray_angle)
{
	// if (ray_angle < 0)
	// 	return (ray_angle += 2 * PI);
	// else if (ray_angle > 2 * PI)
	// 	return (ray_angle -= 2 * PI);
	// else
	// 	return (ray_angle);
	double	angle;

	angle = ray_angle;
	if (ray_angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

/* 
	ray_v = ray_vertical.
	ray_h = ray_horizontal.
 */

void	handle_ray_horizontal_up2(t_ray	*ray, double arc_tan, t_player *p)
{
	ray->end[1] = (((int)p->y >>6) << 6) - 0.0001;
	ray->end[0] = (p->y - ray->end[1]) * arc_tan + p->x;
	ray->y_offset = -64;
	ray->x_offset = -ray->y_offset * arc_tan;
}

void	handle_ray_horizontal_down2(t_ray *ray, double arc_tan, t_player *p)
{
	ray->end[1] = (((int)p->y >> 6) << 6) + 64;
	ray->end[0] = (p->y - ray->end[1]) * arc_tan + p->x;
	ray->y_offset = 64;
	ray->x_offset = -ray->y_offset * arc_tan;
}

void	handle_ray_parallel2(t_ray *ray, t_player *p)
{
	ray->end[0] = p->x;
	ray->end[1] = p->y;
	// dof = 8;
}

double	get_ray_len2(t_ray *ray, t_map *map)
{
	int		mx;
	int		my;
	int		depth_of_field;
	double	length;

	depth_of_field = 0;
	length = 1000000;
	while (depth_of_field < DOF)
	{
		if (ray->angle == 0 || ray->angle == PI)
			break ;
		mx = (int)(ray->end[0]) >> 6;
		my = (int)(ray->end[1]) >> 6;
		if ( mx >= 0 && my >= 0 && mx < map->width && my < map->height && wall_contact_detected(mx, my, map))
		{
			length = dist(map->player->x, map->player->y, ray->end[0], ray->end[1], ray->angle);
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


		// 	// mx = (int)(rx) >> 6;
		// 	// my = (int)(ry) >> 6;
		// 	mx = (int)(ray_h->end[0]) >> 6;
		// 	my = (int)(ray_h->end[1]) >> 6;
		// 	// mp = my * map_width+mx;
		// 	// if (mx >= 0 && mx <= 9 && my >= 0 && my <= 9 && map[my][mx] == '1')
		// 	// if (mp < mapX * mapY && map[my][mx] == '1')
		// 	if ( mx >= 0 && my >= 0 && mx < map->width && my < map->height && wall_contact_detected(mx, my, map))
		// 	{
		// 		// hx=rx; hy = ry; disH=dist(player->x, player->y, hx, hy, ra);
		// 		disH = dist(player->x, player->y, ray_h->end[0], ray_h->end[1], ra);
		// 		// dof=8;
		// 		break ;
		// 	}
		// 	else
		// 	{
		// 		// rx+=xo;
		// 		// ry+=yo;
		// 		ray_h->end[0] += ray_h->x_offset;
		// 		ray_h->end[1] += ray_h->y_offset;
		// 		dof+=1;
		// 	}
		// }
}

t_ray	*ray_horizontal_init2(double ray_angle, int color, t_map *map)
{
	t_player	*p;
	t_ray		*ray;
	double		arc_tan; 

	p = map->player;
	ray = malloc(sizeof(t_ray));
	ray->color = color;
	ray->angle = ray_angle;
	arc_tan = -1/tan(ray_angle);
	if (ray_angle > PI)
		handle_ray_horizontal_up2(ray, arc_tan, p);
	if (ray_angle < PI)
		handle_ray_horizontal_down2(ray, arc_tan, p);
	if (ray_angle == 0 || ray_angle == PI)
		handle_ray_parallel2(ray, p);
	ray->length = get_ray_len2(ray, map);
	return (ray);
}

void	handle_ray_vertical_left2(t_ray *ray, double n_tan, t_player *p)
{
	ray->end[0] = (((int)p->x >> 6) << 6) - 0.0001;
	ray->end[1] = (p->x - ray->end[0]) * n_tan + p->y;
	ray->x_offset = -64;
	ray->y_offset = -ray->x_offset * n_tan;
}

void	handle_ray_vertical_right2(t_ray *ray, double n_tan, t_player *p)
{
	ray->end[0] = (((int)p->x >> 6) << 6) + 64;
	ray->end[1] = (p->x - ray->end[0]) * n_tan + p->y;
	ray->x_offset = 64;
	ray->y_offset = -ray->x_offset * n_tan;
}

t_ray	*ray_vertical_init2(double ray_angle, int color, t_map *map)
{
	t_player	*p;
	t_ray		*ray;
	double		n_tan;
	
	p = map->player;
	ray = malloc(sizeof(t_ray));
	ray->angle = ray_angle;
	ray->color = color;
	n_tan = -tan(ray_angle);
	if (ray_angle > P2 && ray_angle < P3)
		handle_ray_vertical_left2(ray, n_tan, p);
	if (ray_angle < P2 || ray_angle > P3)
		handle_ray_vertical_right2(ray, n_tan, p);
	if (ray_angle == 0 || ray_angle == PI)
		handle_ray_parallel2(ray, p);
	ray->length = get_ray_len2(ray, map);
	return (ray);
}

void	render_rays(t_map *map, t_img *buffer)
{
	int r, mx, my, mp, dof, disT;
	double rx, ry, ra, xo, yo;
	//
	t_player *player;

	int testx = 0;
	int	testy = 0;
	player = map->player;
	ra = player->angle - DEG * 30;
	int	ray_count = -1;
	while (++ray_count < RAY_COUNT)
	{
		// horizontal
		ra = ray_angle_adjust(ra);
		t_ray	*ray_h = ray_horizontal_init2(ra, GREEN, map);
		t_ray	*ray_v = ray_vertical_init2(ra, RED, map);
		
		int	*start0;
		int	*end0;
		if (ray_v->length < ray_h->length)
		{
		start0 = coord_init(player->x, player->y);
		end0 = coord_init(ray_v->end[0], ray_v->end[1]);
		t_line	*line0 = line_init(start0, end0, ray_v->color);
		render_line(line0, buffer);
		free(start0);
		free(end0);
		free(line0);
		}
		else if (ray_h->length < ray_v->length)
		{
		start0 = coord_init(player->x, player->y);
		end0 = coord_init(ray_h->end[0], ray_h->end[1]);
		t_line	*line0 = line_init(start0, end0, ray_h->color);
		render_line(line0, buffer);
		free(start0);
		free(end0);
		free(line0);
		}
		
		free(ray_h);
		free(ray_v);

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
		ra += DEG;
		// if (ra < 0)
		// 	ra += 2 * PI;
		// if (ra > 2 * PI)
		// 	ra -= 2 * PI;
	}
}

// void    render_ray2(t_map *map, t_img *dst_img)
// {
	
// }

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