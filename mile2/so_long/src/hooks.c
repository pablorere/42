/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:27:55 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/09/01 17:50:09 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	limitwall(t_data *data, int xmove, int ymove)
{
	int	nx;
	int	ny;
	int	mx;
	int	my;

	nx = data->position_x + xmove;
	ny = data->position_y + ymove;
	mx = nx / TILE_SIZE;
	my = ny / TILE_SIZE;
	if (out_of_bounds(data, mx, my))
		return ;
	if (data->map[my][mx] == '1')
		return ;
	if (is_exit_blocked(data, data->map[my][mx]))
		return ;
	if (data->map[my][mx] == 'E')
		win_and_exit(data, nx, ny);
	collect_coin(data, mx, my);
	perform_move(data, nx, ny);
}

int	close_hook(void *param)
{
	(void)param;
	exit(0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == KEY_ESC || keycode == KEY_CLICK)
		exit(0);
	if (keycode == KEY_W)
		limitwall(data, 0, -TILE_SIZE);
	else if (keycode == KEY_S)
		limitwall(data, 0, TILE_SIZE);
	else if (keycode == KEY_A)
		limitwall(data, -TILE_SIZE, 0);
	else if (keycode == KEY_D)
		limitwall(data, TILE_SIZE, 0);
	draw(data);
	return (0);
}
