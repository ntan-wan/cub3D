/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:57:41 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/04/11 12:21:46 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// typedef struct s_map

// void	render_minimap(t_map *map, t_img *dst_img)
// {
// 	int	x;
// 	int	y;
	
// 	y = -1;
// 	while (++y < map_height)
// 	{
// 		x = -1;
// 		while (++x < map_width)
// 		{
// 			if (map[y][x] == '1')
// 				render_quad(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE - 4, CELL_SIZE - 4, WHITE, dst_img);
// 			else
// 				render_quad(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE - 4, CELL_SIZE - 4, BLACK, dst_img);
// 		}
// 	}
// }