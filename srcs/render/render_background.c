/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:15:46 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/04/11 11:16:18 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_background(int color, t_img *dst_img)
{
	int	x;
	int	y;

	y = -1;
	while (++y < W_HEIGHT)
	{
		x = -1;
		while (++x < W_WIDTH)
			pixel_img_put(x, y, color, dst_img);
	}
}