/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingkang <mingkang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 10:57:28 by mingkang          #+#    #+#             */
/*   Updated: 2022/12/23 13:46:59 by mingkang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mouse_move(int x, int y, void *vars)
{
	t_data	*data;

	data = (t_data *)vars;
	if (x > 0 && x < SRCN_WDT && y > 0 && y < SRCN_HGT)
	{
		data->handle->prev_x = data->handle->cur_x;
		data->handle->prev_y = data->handle->cur_y;
		data->handle->cur_x = x;
		data->handle->cur_y = y;
		if (data->handle->shift_hold == TRUE && \
			data->handle->wheel_hold == TRUE)
		{
			data->cam->x_offset += x - data->handle->prev_x;
			data->cam->y_offset += y - data->handle->prev_y;
		}
		else if (data->handle->wheel_hold == TRUE)
		{
			data->cam->beta += (x - data->handle->prev_x) * 0.002;
			data->cam->gamma += (y - data->handle->prev_y) * 0.002;
		}
	}
	draw_map(data);
	return (0);
}

int	mouse_press(int button, int x, int y, void *vars)
{
	t_data	*data;

	data = (t_data *)vars;
	if (button == M_WHEEL)
		data->handle->wheel_hold = TRUE;
	else if (button == M_WHEEL_UP)
		data->cam->zoom++;
	else if (button == M_WHEEL_DOWN && data->cam->zoom > 1)
		data->cam->zoom--;
	draw_map(data);
	return (0);
}

int	mouse_release(int button, int x, int y, void *vars)
{
	t_data	*data;

	data = (t_data *)vars;
	data->handle->wheel_hold = FALSE;
	draw_map(data);
	return (0);
}

void	cntl_map(t_data *data)
{
	mlx_hook(data->win_ptr, ON_KEYDOWN, 0, key_press, data);
	mlx_hook(data->win_ptr, ON_KEYUP, 0, key_release, data);
	mlx_hook(data->win_ptr, ON_MOUSEDOWN, 0, mouse_press, data);
	mlx_hook(data->win_ptr, ON_MOUSEUP, 0, mouse_release, data);
	mlx_hook(data->win_ptr, ON_MOUSEMOVE, 0, mouse_move, data);
	mlx_hook(data->win_ptr, ON_DESTROY, 0, exit_hook, data);
}
