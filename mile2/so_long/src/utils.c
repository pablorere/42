/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:21:01 by silvertape        #+#    #+#             */
/*   Updated: 2025/09/13 16:03:35 by ppaula-s         ###   ########.fr       */
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

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 4)
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
		x = -1;
		while (++x < data->map_width)
		{
			if (data->map[y][x] == 'P')
			{
				data->position_x = x * TILE_SIZE;
				data->position_y = y * TILE_SIZE;
				data->map[y][x] = '0';
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

/*
** Libera todos los recursos antes de salir
** Parámetros: data - estructura con todos los recursos
** Retorna: nada (void)
*/
void	cleanup_resources(t_data *data)
{
	if (data->character)
		mlx_destroy_image(data->mlx, data->character);
	if (data->floor)
		mlx_destroy_image(data->mlx, data->floor);
	if (data->wall)
		mlx_destroy_image(data->mlx, data->wall);
	if (data->coin)
		mlx_destroy_image(data->mlx, data->coin);
	if (data->exit)
		mlx_destroy_image(data->mlx, data->exit);
	if (data->exit_open)
		mlx_destroy_image(data->mlx, data->exit_open);
	if (data->window)
		mlx_destroy_window(data->mlx, data->window);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	if (data->map)
		free_map(data->map);
}
