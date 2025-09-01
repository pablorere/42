/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silvertape <silvertape@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:25:08 by silvertape        #+#    #+#             */
/*   Updated: 2025/07/21 15:10:58 by silvertape       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

/*
** Mueve las coordenadas x,y aplicando límites de pantalla
** Parámetros: x, y - punteros a coordenadas actuales
**            xmove, ymove - movimiento a aplicar
** Retorna: nada (void)
*/
void	limitwall(t_data *data , int xmove, int ymove)
{
	data->position_x +=  xmove;
	data->position_y +=  ymove;
	if (data->position_x < 0)
		data->position_x = 0;
	if (data->position_y < 0)
		data->position_y = 0;
	if (data->position_x >= 1216)
		data->position_x = 1216;
	if (data->position_y >= 656)
		data->position_y = 656;
}

/*
** Hook para cerrar la ventana (botón X)
** Parámetros: param - parámetro no usado
** Retorna: 0 (nunca se ejecuta debido a exit)
*/
int	close_hook(void *param)
{
	(void)param;
	exit(0);
}

/*
** Hook para manejar las teclas presionadas (WASD y ESC)
** Parámetros: keycode - código de la tecla presionada, data - datos del juego
** Retorna: 0 siempre
*/
int	key_hook(int keycode, t_data *data)
{
	if (keycode == KEY_ESC || keycode == KEY_CLICK)
		exit(0);
	if (keycode == KEY_W)
		limitwall(data, 0, -TILE_SIZE);
	else if (keycode == KEY_S)
		limitwall(data , 0, TILE_SIZE);
	else if (keycode == KEY_A)
		limitwall(data , -TILE_SIZE, 0);
	else if (keycode == KEY_D)
		limitwall(data , TILE_SIZE, 0);
	draw(data);
	return (0);
}
