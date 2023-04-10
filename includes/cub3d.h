/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:42:52 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/04/10 17:25:23 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <math.h>

# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>

# include "libft.h"

# define SUCCESS 0
# define ERROR 1

# define W_WIDTH 640
# define W_HEIGHT 640

# define CELL_SIZE 64
# define STEP_SIZE 4
# define ROTATE_SIZE 0.04

# define PI 3.14159265

# ifdef __APPLE__
#  define KEY_A 0
#  define KEY_D 2
#  define KEY_W 13
#  define KEY_S 1
#  define ESC 53
#  define SPACE_BAR 49
# else
#  define KEY_A 97
#  define KEY_D 100
#  define KEY_W 119
#  define KEY_S 115
#  define ESC 65307
#  define SPACE_BAR 32
# endif

typedef enum e_color
{
	RED =		0xFF0000,
	GREEN =		0x00FF00,
	BLUE =		0x0000FF,
	WHITE =		0xFFFFFF,
	BLACK =		0x000000,
	GRAY =		0x808080,
	YELLOW =	0xFFFF00,
	MAGNETA =	0xFF00FF,
	CYAN =		0x00FFFF,
	ORANGE =	0xFFA500,
	BROWN =		0xA52A2A,
	PINK =		0xFFC0CB,
	PURPLE =	0x800080,
	TEAL =		0x008080,
}	t_color;

typedef enum e_event
{
	KEYPRESS =			2,
	KEYRELEASE =		3,
	DESTROY_NOTIFY =	17,
}	t_event;

typedef enum e_mask
{
	MASK_KEYPRESS =		1L << 0,
	MASK_KEYRELEASE =	1L << 1,
}	t_mask;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_mlx;

typedef struct s_square
{
	double		x;
	double		y;
	int			width;
	int			height;
	int			color;
}	t_square;

typedef struct s_triangle
{
	double		x;
	double		y;
	int			width;
	int			height;
	int			color;
}	t_triangle;

/* 
	@param bpp bits per pixel.
	@param size_line bytes per row.
 */
typedef struct s_img
{
	int		width;
	int		height;
	int		bpp;
	char	*addr;
	int		endian;
	void	*img_ptr;
	int		size_line;
}	t_img;

typedef struct s_wall
{
	int	x;
	int	y;
}	t_wall;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	double	delta_x;
	double	delta_y;
}	t_player;

typedef struct s_game
{
	t_mlx		*mlx;
	t_player	*player;
}	t_game;

/* ********** RENDER ********** */

// int			render(t_game *game);
// void		render_wall(t_img *buffer_img);
// int			render_square(t_square *sq, t_img *buffer_img);
// void		render_minimap_background(int color, t_img *buffer_img);
// void		render_object_square(int x, int y, int color, t_img *buffer);
// void		render_square_wall(t_wall *wall, int color, t_img *buffer_img);
// void		render_player_square(t_player *player, int color, t_img *buffer_img);
// void		render_player_direction(t_player *player, int color, t_img *buffer_img);

int		render(t_game *game);
void	render_square(int x, int y, int width, int height, int color, t_img *img);

void		img_pixel_put(int x, int y, int color, t_img *img);
t_square	*sq_init(double x, double y, int width, int height, int color);

int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue);
#endif