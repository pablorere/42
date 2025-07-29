/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silvertape <silvertape@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:21:01 by silvertape        #+#    #+#             */
/*   Updated: 2025/07/21 15:02:14 by silvertape       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

/*
** Valida que el nombre del archivo tenga extensión .ber
** Parámetros: filename - nombre del archivo a validar
** Retorna: 1 si tiene extensión .ber, 0 si no
*/
int	validate_ber_extension(char *filename)
{
	int	len;

	if (!filename || (len = ft_strlen(filename)) < 4)
		return (0);
	return (!ft_strncmp(filename + len - 4, ".ber", 4));
}

/*
** Libera la memoria de un array de strings del mapa
** Parámetros: map - array de strings a liberar
** Retorna: nada (void)
*/
void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
}

/*
** Encuentra la posición del jugador ('P') en el mapa
** Parámetros: data - estructura con el mapa y donde guardar la posición
** Retorna: 1 si encontró al jugador, 0 si no
*/
int	find_player_position(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < data->map_height)
	{
		write(1, data->map[y], ft_strlen(data->map[y]));
		write(1, "\n", 1);
		x = -1;
		while (++x < data->map_width)
		{
			if (data->map[y][x] == 'P')
			{
				data->position_x = x * TILE_SIZE;
				data->position_y = y * TILE_SIZE;
				return (1);
			}
		}
	}
	return (0);
}

void	floodfill(char **map, int x, int y)
{
	if (map[x][y] == '1' || map[x][y] == 'X')
		return ;
	map[x][y] = 'X';
	floodfill(map, x + 1, y);
	floodfill(map, x - 1, y);
	floodfill(map, x, y + 1);
	floodfill(map, x, y - 1);
	return ;
}