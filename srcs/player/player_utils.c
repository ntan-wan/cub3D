/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 23:05:56 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/04/18 07:21:10 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* 
	@note angle in radian.
 */
int	player_angle_init(char orientation)
{
	if (orientation == 'E')
		return (0);
	else if (orientation == 'S')
		return (PI / 2);
	else if (orientation == 'W')
		return (PI);
	else if (orientation == 'N')
		return (3 * (PI / 2));
}

t_player	*player_init(int x, int y, char orientation)
{
	t_player	*p;

	p = ft_calloc(1, sizeof(t_player));
	if (p)
	{
		ft_memcpy(p->coord, (double [2]){x, y}, sizeof(p->coord));
		p->orientation = orientation;
		p->angle = player_angle_init(orientation);
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