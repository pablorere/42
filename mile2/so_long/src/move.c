/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:06:00 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/09/01 17:55:08 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	out_of_bounds(t_data *data, int mx, int my)
{
	if (mx < 0 || my < 0)
		return (1);
	if (mx >= data->map_width || my >= data->map_height)
		return (1);
	return (0);
}

void	win_and_exit(t_data *data, int new_x, int new_y)
{
	data->position_x = new_x;
	data->position_y = new_y;
	data->move_count++;
	printf("Movimientos válidos: %d\n", data->move_count);
	printf("Has recogido todas las monedas. ¡Victoria!\n");
	draw(data);
	exit(0);
}

int	is_exit_blocked(t_data *data, char tile)
{
	if (tile != 'E')
		return (0);
	if (data->coins_collected < data->total_coins)
		return (1);
	return (0);
}

void	collect_coin(t_data *data, int mx, int my)
{
	if (data->map[my][mx] == 'C')
	{
		data->map[my][mx] = '0';
		data->coins_collected++;
	}
}

void	perform_move(t_data *data, int nx, int ny)
{
	data->position_x = nx;
	data->position_y = ny;
	data->move_count++;
	printf("Movimientos válidos: %d\n", data->move_count);
}
