/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 07:51:10 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/04/16 13:59:13 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	map_max_width_get(t_list *map_list)
{
	int		strlen;
	int		max_strlen;

	max_strlen = INT_MIN;
	while (map_list)
	{
		strlen = ft_strlen((char *)map_list->content) - 1;
		if (strlen > max_strlen)
			max_strlen = strlen;
		map_list = map_list->next;
	}
	return (max_strlen);
}

t_list	*map_list_init(char *path_to_file)
{
	int		fd;
	char	*line;
	t_list	*map_list;

	map_list = NULL;
	fd = open(path_to_file, O_RDONLY, 0644);
	line = get_next_line(fd);
	while (line)
	{
		ft_lstadd_back(&map_list, ft_lstnew(ft_strdup(line)));
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (map_list);
}

t_player	*map_player_init(t_list *map_list)
{
	int			x;
	int			y;
	char		c;
	t_player	*p;
	t_list		*lst;

	y = -1;
	p = NULL;
	lst = map_list;
	while (lst)
	{
		++y;
		x = -1;
		while (((char *)lst->content)[++x])
		{
			c = ((char *)lst->content)[x];
			if (ft_strchr("NSWE", c))
				p = player_init(x * CELL_SIZE, y * CELL_SIZE, c);
		}
		lst = lst->next;
	}
	return (p);
}

t_map	*map_init(t_list *map_list)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (map)
	{
		map->list = map_list;
		map->width = map_max_width_get(map_list);
		map->height = ft_lstsize(map_list);
		map->player = map_player_init(map_list);
	}
	return (map);
}