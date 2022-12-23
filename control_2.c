/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingkang <mingkang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 10:57:28 by mingkang          #+#    #+#             */
/*   Updated: 2022/12/23 13:12:05 by mingkang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_press(int keycode, void *vars)
{
	t_data	*data;

	data = (t_data *)vars;
	if (keycode == K_SHIFT)
		data->handle->shift_hold = TRUE;
	else if (keycode == K_CODE_P || keycode == K_CODE_I || keycode == K_CODE_O)
	{
		set_projection(keycode, data);
	}
	else if (keycode == K_CODE_Q || keycode == K_CODE_W)
	{
		if (keycode == K_CODE_Q)
			data->cam->alpha += 0.04;
		else
			data->cam->alpha -= 0.04;
	}
	else if (keycode == K_CODE_A || keycode == K_CODE_S)
	{
		if (keycode == K_CODE_A)
			data->cam->beta += 0.04;
		else
			data->cam->beta -= 0.04;
	}
	else if (keycode == K_CODE_Z || keycode == K_CODE_X)
	{
		if (keycode == K_CODE_Z)
			data->cam->gamma += 0.04;
		else
			data->cam->gamma -= 0.04;
	}
	else if (keycode == K_CODE_ZU || keycode == K_CODE_ZD)
	{
		if (keycode == K_CODE_ZD)
			data->cam->z_factor++;
		else if (data->cam->z_factor > 1)
			data->cam->z_factor--;
	}
	else if (keycode == K_ESC)
		exit(EXIT_SUCCESS);
	draw_map(data);
	return (0);
}

int	key_release(int keycode, void *vars)
{
	t_data	*data;

	data = (t_data *)vars;
	data->handle->shift_hold = 0;

	draw_map(data);
	return (0);
}
