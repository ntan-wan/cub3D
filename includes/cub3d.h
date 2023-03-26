/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:42:52 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/26 18:25:32 by ntan-wan         ###   ########.fr       */
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

# define W_WIDTH 800
# define W_HEIGHT 800

# define PIXEL_SIZE 32

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
	int		x;
	int		y;
	int		width;
	int		height;
	int		color;
}	t_square;

/* 
	@param bpp bits per pixel.
	@param size_line bytes per row.
 */
typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_wall
{
	int	x;
	int	y;
}	t_wall;

typedef struct s_direction
{
	double	angle;
	double	delta_x;
	double	delta_y;
}	t_direction;

typedef struct s_player
{
	double	x;
	double	y;
	// double	angle;
	// double	delta_x;
	// double	delta_y;
	t_direction	direction;
}	t_player;

typedef struct s_game
{
	t_mlx		*mlx;
	t_player	*player;
}	t_game;

#endif