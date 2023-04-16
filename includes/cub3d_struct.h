/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:12:19 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/04/16 14:36:27 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCT_H
# define CUB3D_STRUCT_H

/* ********** INIT ********** */

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_mlx;

typedef struct s_player
{
	char	orientation;
	double	x;
	double	y;
	double	angle;
	double	delta_x;
	double	delta_y;
}	t_player;

typedef struct s_map
{
	int			width;
	int			height;
	t_player	*player;
	t_list		*list;
}	t_map;

typedef struct s_game
{
	t_mlx		*mlx;
	t_map		*map;
	// t_player	*player;
}	t_game;

/* ********** RENDER ********** */

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

/* 
	@param bpp bits per pixel.
	@param size_line bytes per row.
	@param img_ptr stores ptr returned by mlx_new_image().
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

typedef struct s_block
{
	int	color;
	int	width;
	int	height;
	int	coord[2];
}	t_block;

typedef struct s_line
{
	int	color;
	int	delta_x;
	int	delta_y;
	int	start[2];
	int	end[2];
}	t_line;

/* *********** EVENTS ********** */

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

#endif