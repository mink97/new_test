/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingkang <mingkang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 07:53:42 by mingkang          #+#    #+#             */
/*   Updated: 2022/12/23 21:47:49 by mingkang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	map->bg_color = GRAY;
	data = init_mlx(map);
	init_camera(data);
	data->cam->prjc = ISOMETRIC;
	draw_map(data);
	cntl_map(data);
	mlx_loop(data->mlx_ptr);
}
