/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_block.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 05:33:47 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/04/11 12:06:24 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	block_set_color(t_block *block, int color)
{
	if (block)
		block->color = color;
}

t_block	*block_init(int coord[2], int width, int height, int color)
{
	t_block	*block;

	block = malloc(sizeof(t_block));
	if (block)
	{
		block->color = color;
		block->width = width;
		block->height = height;
		ft_memcpy(block->coord, coord, 2 * sizeof(int));
	}
	return (block);
}

void	render_block(t_block *block, t_img *dst_img)
{
	int	x;
	int	y;

	y = block->coord[1];
	while (y < block->coord[1] + block->height)
	{
		x = block->coord[0];
		while (x < block->coord[0] + block->width)
		{
			pixel_img_put(x, y, block->color, dst_img);
			x++;
		}
		y++;
	}
}

void	render_block_object(int x, int y, int color, t_img *dst_img)
{
	render_block(&(t_block){color, CELL_SIZE, CELL_SIZE, {x, y}}, dst_img);
}

void	block_free(t_block **block)
{
	if (*block)
		free(*block);
	*block = NULL;
}
