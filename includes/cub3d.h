/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:42:52 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/04/11 12:27:07 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdbool.h>

# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>

# include "libft.h"
# include "cub3d_struct.h"
# include "cub3d_define.h"

void		pixel_img_put(int x, int y, int color, t_img *img);
int			pixel_encode_rgb(uint8_t red, uint8_t green, uint8_t blue);

/* ********** PLAYER ********** */

t_player	*player_init(int x, int y);
void		player_free(t_player **player);
void		player_rotate_left(t_player *player);
void		player_rotate_right(t_player *player);
void		player_move_forward(t_player *player);
void		player_move_backward(t_player *player);

/* ********** RENDER ********** */

//line
void		line_free(t_line **line);
void		render_line(t_line *line, t_img *dst_img);
t_line		*line_init(int start[2], int end[2], int color);

//quad
void		quad_free(t_quad **sq);
void		render_quad(t_quad *sq, t_img *dst_img);
t_quad		*quad_init(int coord[2], int width, int height, int color);

void		render_background(int color, t_img *img);

int		render(t_game *game);



int			handle_keypress(int keycode, t_game *game);
int			*coord_init(int x, int y);
#endif