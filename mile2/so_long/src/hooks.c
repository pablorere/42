/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silvertape <silvertape@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:25:08 by silvertape        #+#    #+#             */
/*   Updated: 2025/07/07 16:34:21 by silvertape       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

/*
** Mueve las coordenadas x,y aplicando límites de pantalla
** Parámetros: x, y - punteros a coordenadas actuales
**            xmove, ymove - movimiento a aplicar
** Retorna: nada (void)
*/
void	limitwall(int *x, int *y, int xmove, int ymove)
{
	*x = *x + xmove;
	*y = *y + ymove;
	if (*x < 0)
		*x = 0;
	if (*y < 0)
		*y = 0;
	if (*x >= 1216)
		*x = 1216;
	if (*y >= 656)
		*y = 656;
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
		limitwall(&data->position_x, &data->position_y, 0, -64);
	else if (keycode == KEY_S)
		limitwall(&data->position_x, &data->position_y, 0, 64);
	else if (keycode == KEY_A)
		limitwall(&data->position_x, &data->position_y, -64, 0);
	else if (keycode == KEY_D)
		limitwall(&data->position_x, &data->position_y, 64, 0);
	draw(data);
	return (0);
}
