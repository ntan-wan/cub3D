/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:57:41 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/04/18 07:18:23 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_mini_wall(int x, int y, int color, t_img *dst_img)
{
	render_block_object(x, y, color, dst_img);
}

void	render_mini_walls(t_map *map, int color, t_img *dst_img)
{
	int		x;
	int		y;
	char	c;
	t_list	*map_list;

	y = -1;
	map_list = map->list;
	while (map_list)
	{
		++y;
		x = -1;
		while (((char *)map_list->content)[++x])
		{
			c = ((char *)map_list->content)[x];
			if (c == '1')
				render_mini_wall(x * CELL_SIZE, y * CELL_SIZE, color, dst_img);
		}
		map_list = map_list->next;
	}
}

void	render_mini_player(t_player *p, int color, t_img *dst_img)
{
	render_block_object(p->coord[0], p->coord[1], color, dst_img);
}

void	render_mini_map(t_map *map, t_img *dst_img)
{
	render_mini_walls(map, WHITE, dst_img);
	render_mini_player(map->player, YELLOW, dst_img);
}
