/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 15:22:44 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/09/13 15:59:06 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
#include <stdio.h>

void	map_to_screen(int map_x, int map_y, int *screen_x, int *screen_y)
{
	*screen_x = map_x * TILE_SIZE;
	*screen_y = map_y * TILE_SIZE;
}

void	draw_tile(t_data *data, int x, int y)
{
	int	screen_x;
	int	screen_y;

	map_to_screen(x, y, &screen_x, &screen_y);
	if (data->floor && data->map[y][x] != '1')
		mlx_put_image_to_window(data->mlx, data->window,
			data->floor, screen_x, screen_y);
	if (data->map[y][x] == '1' && data->wall)
		mlx_put_image_to_window(data->mlx, data->window,
			data->wall, screen_x, screen_y);
	else if (data->map[y][x] == 'C' && data->coin)
		mlx_put_image_to_window(data->mlx, data->window,
			data->coin, screen_x, screen_y);
	else if (data->map[y][x] == 'E')
		draw_exit(data, screen_x, screen_y);
}

void	draw_map(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			draw_tile(data, x, y);
			x++;
		}
		y++;
	}
	draw_player(data);
}

void	draw_exit(t_data *data, int screen_x, int screen_y)
{
	if (data->coins_collected == data->total_coins)
		mlx_put_image_to_window(data->mlx, data->window,
			data->exit_open, screen_x, screen_y);
	else
		mlx_put_image_to_window(data->mlx, data->window,
			data->exit, screen_x, screen_y);
}

void	draw_player(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->window,
		data->character, data->position_x, data->position_y);
}
