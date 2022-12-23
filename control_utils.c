/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingkang <mingkang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 10:57:30 by mingkang          #+#    #+#             */
/*   Updated: 2022/12/23 13:12:05 by mingkang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_projection(int key_code, t_data *data)
{
	init_camera(data);
	if (key_code == K_CODE_P)
		data->cam->prjc = PARALLEL;
	else if (key_code == K_CODE_O)
		data->cam->prjc = OBLIQUE;
	else if (key_code == K_CODE_I)
		data->cam->prjc = ISOMETRIC;
	draw_map(data);
}

int	exit_hook(void *vars)
{
	exit(0);
}
