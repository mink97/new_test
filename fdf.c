/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingkang <mingkang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 07:53:42 by mingkang          #+#    #+#             */
/*   Updated: 2022/12/23 16:24:52 by mingkang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	show_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height * map->width)
	{
		printf("|%d/%d/%d/%x|", map->nodes[i].x, map->nodes[i].y, map->nodes[i].z, map->nodes[i].color);
		if (i % map->width == map->width - 1)
			printf("\n");
		i++;
	}
	printf("---------------------------------\n");
}

int	main(int argc, char **argv)
{
	char	*str;
	t_list	*lst;
	t_map	*map;
	t_data	*data;

	map = malloc(sizeof(t_map) * 1);
	if (map == NULL)
		ft_error("error - failed to malloc map");
	lst = NULL;
	parse_map(argv, map, &lst);
	map->nodes = malloc(sizeof(t_point) * map->width * map->height);
	if (map->nodes == NULL)
		ft_error("error - failed to malloc map->nodes");
	read_map(map, &lst);
	// show_map(map);
	data = init_mlx(map);
	init_camera(data);
	draw_map(data);
	cntl_map(data);
	mlx_loop(data->mlx_ptr);
}
