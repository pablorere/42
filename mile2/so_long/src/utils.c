/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silvertape <silvertape@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 02:47:04 by silvertape        #+#    #+#             */
/*   Updated: 2025/07/09 23:11:54 by silvertape       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	validate_ber_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (!filename || len < 4)
		return (0);
	return (!ft_strncmp(filename + len - 4, ".ber", 4));
}

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
}

int iswalkable()