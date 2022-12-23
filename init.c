/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingkang <mingkang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 10:57:36 by mingkang          #+#    #+#             */
/*   Updated: 2022/12/23 16:34:56 by mingkang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
// #define DEBUG

void	init_camera(t_data *data)
{
	data->cam->alpha = 0;
	data->cam->beta = 0;
	data->cam->gamma = 0;
	data->cam->x_offset = 0;
	data->cam->y_offset = 0;
	data->cam->zoom = \
	get_min((SRCN_WDT) / data->map->width, (SRCN_HGT) / data->map->height) / 2;
	data->cam->z_factor = 1;
}

t_data	*init_mlx(t_map *map)
{
	t_data		*data;

	data = malloc(sizeof(t_data) * 1);
	if (data == NULL)
		ft_error("error - failed to malloc data");
	data->mlx_ptr = mlx_init();
	data->win_ptr = \
		mlx_new_window(data->mlx_ptr, SRCN_WDT, SRCN_HGT, "42seoul-fdf");
	data->img = mlx_new_image(data->mlx_ptr, SRCN_WDT, SRCN_HGT);
	if (data->mlx_ptr == NULL || data->win_ptr == NULL || data->img == NULL)
		ft_error("error - failed to initialize mlx");
	data->addr = mlx_get_data_addr(data->img, \
		&(data->bpp), &(data->size_line), &(data->endn));
	data->map = map;
	data->cam = malloc(sizeof(t_camera) * 1);
	if (data->cam == NULL)
		ft_error("error - failed to malloc camera");
	data->handle = malloc(sizeof(t_handle) * 1);
	if (data->handle == NULL)
		ft_error("error - failed to malloc handle");
	return (data);
}

void	parse_map(char **argv, t_map *map, t_list **lst)
{
	int		i;
	int		fd;
	char	*line;
	char	**strs;
	t_list	*new;

	i = 0;
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	map->width = word_cnt(line, ' ');
	while (line > 0)
	{
		strs = ft_split(line, ' ');
		new = ft_lstnew(strs);
		ft_lstadd_back(lst, new);
		line = get_next_line(fd);
		i++;
	}
	map->height = i;
	close(fd);
}

void	fill_node(t_point *node, char **strs, int x, int y)
{
	char	**buf;

	buf = ft_split(*strs, ',');
	node->x = x;
	node->y = y;
	node->z = ft_atoi(buf[0]);
	if (buf[1])
		node->color = ft_atoi_base(&buf[1][2], "0123456789ABCDEF", 16);
	else
		node->color = 0xffffff;
	free_strs(buf);
}

void	read_map(t_map *map, t_list **lst)
{
	int		i;
	int		j;
	int		k;
	char	**strs;
	t_list	*tmp;

	tmp = *lst;
	k = 0;
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		strs = tmp->content;
		while (++j < map->width)
			fill_node(map->nodes + (k++), strs + j, j, i);
		tmp = tmp->next;
	}
	ft_lstclear(lst, free);
}
// void	read_map(t_map *map, t_list **lst)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	char	**strs;
// 	char	**buf;
// 	t_list	*tmp;

// 	tmp = *lst;
// 	k = 0;
// 	i = -1;
// 	while (++i < map->height)
// 	{
// 		j = -1;
// 		strs = tmp->content;
// 		while (++j < map->width)
// 		{
// 			buf = ft_split(*(strs++), ',');
// 			map->nodes[k].x = j;
// 			map->nodes[k].y = i;
// 			map->nodes[k].z = ft_atoi(buf[0]);
// 			if (buf[1])
// 				map->nodes[k].color = ft_atoi_base(&buf[1][2], "0123456789ABCDEF", 16);
// 			else
// 				map->nodes[k].color = 0xffffff;
// 			k++;
// 			free_strs(buf);
// 		}
// 		tmp = tmp->next;
// 	}
// 	ft_lstclear(lst, free);
// }
