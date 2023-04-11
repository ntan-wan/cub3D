/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_player_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 23:05:56 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/04/10 23:06:42 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player	*player_init(int x, int y)
{
	t_player	*p;

	p = ft_calloc(1, sizeof(t_player));
	if (p)
	{
		p->x = x * CELL_SIZE;
		p->y = y * CELL_SIZE;
		p->delta_x = cos(p->angle) * STEP_SIZE;
		p->delta_y = sin(p->angle) * STEP_SIZE;
	}
	return (p);
}

void	player_free(t_player **player)
{
	t_player	*p;

	p = *player;
	free(p);
	*player = NULL;
}