/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silvertape <silvertape@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:25:04 by silvertape        #+#    #+#             */
/*   Updated: 2025/07/09 23:10:33 by silvertape       ###   ########.fr       */
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
			"textures/character_simple.xpm", &x, &y);
	data->floor = mlx_xpm_file_to_image(data->mlx,
			"textures/floor_simple.xpm", &x, &y);
	data->wall = mlx_xpm_file_to_image(data->mlx,
			"textures/wall_simple.xpm", &x, &y);
	if (!data->wall)
		write(1, "Error: No se pudo cargar wall.xpm\n", 34); 
	if (!data->floor)
		write(1, "Error: No se pudo cargar floor.xpm\n", 35);
	if (!data->character)
		write(1, "Error: No se pudo cargar character.xpm\n", 39);
}

/*
** Renderiza toda la pantalla: mapa + personaje
** Parámetros: data - estructura con todos los datos del juego
** Retorna: nada (void)
*/
void	draw(t_data *data)
{
	mlx_clear_window(data->mlx, data->window);
	fileloader(data);
	draw_map(data);
	if (data->character)
		mlx_put_image_to_window(data->mlx, data->window, data->character,
			data->position_x, data->position_y);
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
** Dibuja todo el mapa en la pantalla según los caracteres del archivo
** Parámetros: data - estructura con el mapa y las texturas
** Retorna: nada (void)
*/
void	draw_map(t_data *data)
{
	int		x;
	int		y;
	int		sx;
	int		sy;

	y = -1;
	while (++y < data->map_height)
	{
		x = -1;
		while (++x < data->map_width)
		{
			map_to_screen(x, y, &sx, &sy);
			if (data->map[y][x] != '1' && data->floor)
				mlx_put_image_to_window(data->mlx, data->window,
					data->floor, sx, sy);
			if (data->map[y][x] == '1' && data->wall)
				mlx_put_image_to_window(data->mlx, data->window,
					data->wall, sx, sy);
		}
	}
}
