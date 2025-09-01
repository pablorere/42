/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:25:04 by silvertape        #+#    #+#             */
/*   Updated: 2025/09/01 17:52:32 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

/*
** Carga las texturas XPM necesarias para el juego
** Parámetros: data - estructura donde almacenar las texturas
** Retorna: nada (void)
*/
void	fileloader(t_data *data)
{
	int	x;
	int	y;

	data->character = mlx_xpm_file_to_image(data->mlx,
			"textures/player_up.xpm", &x, &y);
	data->floor = mlx_xpm_file_to_image(data->mlx,
			"textures/floor.xpm", &x, &y);
	data->wall = mlx_xpm_file_to_image(data->mlx,
			"textures/wall.xpm", &x, &y);
	data->coin = mlx_xpm_file_to_image(data->mlx,
			"textures/coin.xpm", &x, &y);
	data->exit = mlx_xpm_file_to_image(data->mlx,
			"textures/exit_closed.xpm", &x, &y);
	data->exit_open = mlx_xpm_file_to_image(data->mlx,
			"textures/exit_opened.xpm", &x, &y);
	if (!data->wall || !data->floor || !data->character || !data->coin
		|| !data->exit || !data->exit_open)
		write(1, "Error: No se pudo cargar alguna textura\n", 34);
}

/*
** Renderiza toda la pantalla: mapa + personaje
** Parámetros: data - estructura con todos los datos del juego
** Retorna: nada (void)
*/
void	draw(t_data *data)
{
	char	*moves;
	char	*coins;
	char	*total;

	mlx_clear_window(data->mlx, data->window);
	draw_map(data);
	if (data->character)
		mlx_put_image_to_window(data->mlx, data->window, data->character,
			data->position_x, data->position_y);
	moves = ft_itoa(data->move_count);
	coins = ft_itoa(data->coins_collected);
	total = ft_itoa(data->total_coins);
	if (moves && coins && total)
	{
		mlx_string_put(data->mlx, data->window, 10, 20, 0xFFFFFF, "Moves:");
		mlx_string_put(data->mlx, data->window, 70, 20, 0xFFFFFF, moves);
		mlx_string_put(data->mlx, data->window, 10, 40, 0xFFFFFF, "Coins:");
		mlx_string_put(data->mlx, data->window, 70, 40, 0xFFFFFF, coins);
		mlx_string_put(data->mlx, data->window, 90, 40, 0xFFFFFF, "/");
		mlx_string_put(data->mlx, data->window, 100, 40, 0xFFFFFF, total);
	}
	free(moves);
	free(coins);
	free(total);
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

/*
** Dibuja un tile en la pantalla según el carácter del archivo
** Parámetros: data - estructura con el mapa y las texturas
**             pos - puntero a la estructura con las posiciones del tile
** Retorna: nada (void)
*/
static void	draw_tile(t_data *data, t_tilepos *pos)
{
	if (data->map[pos->y][pos->x] != '1' && data->floor)
		mlx_put_image_to_window(data->mlx, data->window,
			data->floor, pos->sx, pos->sy);
	if (data->map[pos->y][pos->x] == '1' && data->wall)
		mlx_put_image_to_window(data->mlx, data->window,
			data->wall, pos->sx, pos->sy);
	if (data->map[pos->y][pos->x] == 'C' && data->coin)
		mlx_put_image_to_window(data->mlx, data->window,
			data->coin, pos->sx, pos->sy);
	if (data->map[pos->y][pos->x] == 'E')
	{
		if (data->coins_collected >= data->total_coins && data->exit_open)
			mlx_put_image_to_window(data->mlx, data->window,
				data->exit_open, pos->sx, pos->sy);
		else if (data->exit)
			mlx_put_image_to_window(data->mlx, data->window,
				data->exit, pos->sx, pos->sy);
	}
}

/*
** Dibuja todo el mapa en la pantalla según los caracteres del archivo
** Parámetros: data - estructura con el mapa y las texturas
** Retorna: nada (void)
*/
void	draw_map(t_data *data)
{
	int			x;
	int			y;
	int			sx;
	int			sy;
	t_tilepos	pos;

	y = -1;
	while (++y < data->map_height)
	{
		x = -1;
		while (++x < data->map_width)
		{
			map_to_screen(x, y, &sx, &sy);
			pos.x = x;
			pos.y = y;
			pos.sx = sx;
			pos.sy = sy;
			draw_tile(data, &pos);
		}
	}
}
