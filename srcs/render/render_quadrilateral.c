/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_quad.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 05:33:47 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/04/11 12:06:24 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_quad	*quad_init(int coord[2], int width, int height, int color)
{
	t_quad	*quad;

	quad = malloc(sizeof(t_quad));
	if (quad)
	{
		quad->color = color;
		quad->width = width;
		quad->height = height;
		ft_memcpy(quad->coord, coord, 2 * sizeof(int));
	}
	return (quad);
}

void	render_quad(t_quad *quad, t_img *dst_img)
{
	int	x;
	int	y;

	y = quad->coord[1];
	while (y < y + quad->height)
	{
		x = quad->coord[0];
		while (x < x + quad->width)
		{
			pixel_img_put(x, y, quad->color, dst_img);
			x++;
		}
		y++;
	}
}

void	quad_free(t_quad **quad)
{
	if (*quad)
		free(*quad);
	*quad = NULL;
}
