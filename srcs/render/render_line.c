/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 06:00:01 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/04/11 21:12:55 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_step_direction(int start_point, int end_point)
{
	if (start_point < end_point)
		return (1);
	else
		return (-1);
}

static bool	is_out_of_bounds(int coord[2])
{
	return (coord[0] < 0 || coord[0] > W_WIDTH
		|| coord[1] < 0 || coord[1] > W_HEIGHT);
}

t_line	*line_init(int start[2], int end[2], int color)
{
	t_line	*line;

	line = malloc(sizeof(t_line));
	if (line)
	{
		line->color = color;
		ft_memcpy(line->start, start, 2 * sizeof(int));
		ft_memcpy(line->end, end, 2 * sizeof(int));
		line->delta_x = abs(start[0] - end[0]);
		line->delta_y = abs(start[1] - end[1]);
	}
	return (line);
}

void	render_line(t_line *line, t_img *dst_img)
{
	int	err;
	int	err_2;
	int	step_x;
	int	step_y;

	step_x = get_step_direction(line->start[0], line->end[0]);
	step_y = get_step_direction(line->start[1], line->end[1]);
	err = line->delta_x - line->delta_y;
	while (line->start[0] != line->end[0] || line->start[1] != line->end[1])
	{
		if (is_out_of_bounds(line->start))
			break ;
		pixel_img_put(line->start[0], line->start[1], line->color, dst_img);
		err_2 = 2 * err;
		if (err_2 > -1 * line->delta_y)
		{
			err -= line->delta_y;
			line->start[0] += step_x;
		}
		if (err_2 < line->delta_x)
		{
			err += line->delta_x;
			line->start[1] += step_y;
		}
	}
}

void	line_free(t_line **line)
{
	if (*line)
		free(*line);
	*line = NULL;
}