/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_put_pixel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 23:57:04 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/04/11 12:40:25 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	pixel_encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red <<16 | green << 8 | blue);
}

void	pixel_img_put(int x, int y, int color, t_img *img)
{
	int		i;
	char	*pixel;	

	i = img->bpp - 8;
	pixel = img->addr + (y * img->size_line + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}