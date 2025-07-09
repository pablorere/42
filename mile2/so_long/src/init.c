/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silvertape <silvertape@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:25:00 by silvertape        #+#    #+#             */
/*   Updated: 2025/07/09 02:46:53 by silvertape       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

/*
** Inicializa MLX y crea la ventana
** Parámetros: data - estructura de datos del juego
** Retorna: 1 si éxito, 0 si error
*/
int	init_mlx(t_data *data)
{
	int	window_width;
	int	window_height;

	data->position_x = 0;
	data->position_y = 0;
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		free_map(data->map);
		return (0);
	}
	window_width = data->map_width * TILE_SIZE;
	window_height = data->map_height * TILE_SIZE;
	data->window = mlx_new_window(data->mlx, window_width, window_height,
			"so_long");
	if (!data->window)
	{
		free_map(data->map);
		return (0);
	}
	return (1);
}

/*
** Configura los hooks y ejecuta el game loop
** Parámetros: data - estructura de datos del juego
** Retorna: nada (void)
*/
void	setup_game(t_data *data)
{
	if (!find_player_position(data))
	{
		write(2, "Error: No se encontró al jugador (P) en el mapa\n", 48);
		return ;
	}
	draw(data);
	mlx_key_hook(data->window, key_hook, data);
	mlx_hook(data->window, 17, 0, close_hook, data);
	mlx_loop(data->mlx);
}
