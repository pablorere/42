/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silvertape <silvertape@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 08:30:00 by silvertape        #+#    #+#             */
/*   Updated: 2025/07/29 08:39:19 by silvertape       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	draw_tile(t_data *data, int x, int y)
{
	int	sx;
	int	sy;

	map_to_screen(x, y, &sx, &sy);
	if (data->map[y][x] != '1' && data->game.floor)
		mlx_put_image_to_window(data->screen.mlx, data->screen.window,
			data->game.floor, sx, sy);
	if (data->map[y][x] == '1' && data->game.wall)
		mlx_put_image_to_window(data->screen.mlx, data->screen.window,
			data->game.wall, sx, sy);
	if (data->map[y][x] == 'C' && data->game.coin)
		mlx_put_image_to_window(data->screen.mlx, data->screen.window,
			data->game.coin, sx, sy);
	if (data->map[y][x] == 'E')
	{
		if (data->game.coins_collected >= data->game.total_coins
			&& data->game.exit_open)
			mlx_put_image_to_window(data->screen.mlx, data->screen.window,
				data->game.exit_open, sx, sy);
		else if (data->game.exit)
			mlx_put_image_to_window(data->screen.mlx, data->screen.window,
				data->game.exit, sx, sy);
	}
}

/*
** Dibuja todo el mapa en la pantalla según los caracteres del archivo
** Parámetros: data - estructura con el mapa y las texturas
** Retorna: nada (void)
*/
void	draw_map(t_data *data)
{
	int		x;
	int		y;

	y = -1;
	while (++y < data->screen.map_height)
	{
		x = -1;
		while (++x < data->screen.map_width)
		{
			draw_tile(data, x, y);
		}
	}
}

/*
** Convierte coordenadas del mapa a coordenadas de pantalla
** Parámetros: map_x, map_y - coordenadas en el mapa
**            screen_x, screen_y - punteros a coordenadas de pantalla
** Retorna: nada (void)
*/
void	map_to_screen(int map_x, int map_y, int *screen_x, int *screen_y)
{
	*screen_x = map_x * TILE_SIZE;
	*screen_y = map_y * TILE_SIZE;
}
