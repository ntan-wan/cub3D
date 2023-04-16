/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:42:52 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/04/16 14:40:28 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>

// open()
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>

# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>

# include "libft.h"
# include "cub3d_struct.h"
# include "cub3d_define.h"

void		pixel_img_put(int x, int y, int color, t_img *img);
int			pixel_encode_rgb(uint8_t red, uint8_t green, uint8_t blue);

/* ********** PLAYER ********** */

void		player_free(t_player **player);
void		player_rotate_left(t_player *player);
void		player_rotate_right(t_player *player);
void		player_move_forward(t_player *player);
void		player_move_backward(t_player *player);
t_player	*player_init(int x, int y, char orientation);

/* ********** MAP ********** */

t_map	    *map_init(t_list *map_list);
t_list	    *map_list_init(char *file_name);

/* ********** RENDER ********** */

//line
void		line_free(t_line **line);
void		render_line(t_line *line, t_img *dst_img);
t_line		*line_init(int start[2], int end[2], int color);

//block
void		block_free(t_block **block);
void	    block_set_color(t_block *block, int color);
void		render_block(t_block *block, t_img *dst_img);
t_block		*block_init(int coord[2], int width, int height, int color);
void		render_block_object(int x, int y, int color, t_img *dst_img);
// void		render_block_object(int coord[2], int color, t_img *dst_img);

// map
void 		render_mini_map(t_map *map, t_img *dst_img);
void	    render_mini_walls(t_map *map, int color, t_img *dst_img);
void	    render_mini_player(t_player *p, int color, t_img *dst_img);


void		render_background(int color, t_img *img);

int		render(t_game *game);


t_map	    *map_init(t_list *map_list);
t_list	*map_list_init(char *path_to_file);
t_player	*map_player_init(t_list *map_list);

int			handle_keypress(int keycode, t_game *game);
int			*coord_init(int x, int y);
#endif