/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileloader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:00:00 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/09/13 16:03:34 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
#include <stdio.h>

void	load_player_and_floor(t_data *data)
{
	data->character = mlx_xpm_file_to_image(data->mlx,
			"textures/player_down.xpm", &data->img_width, &data->img_height);
	if (!data->character)
		printf("Error loading player_down.xpm\n");
	data->floor = mlx_xpm_file_to_image(data->mlx,
			"textures/floor.xpm", &data->img_width, &data->img_height);
	if (!data->floor)
		printf("Error loading floor.xpm\n");
}

void	load_wall_and_coin(t_data *data)
{
	data->wall = mlx_xpm_file_to_image(data->mlx,
			"textures/wall.xpm", &data->img_width, &data->img_height);
	if (!data->wall)
		printf("Error loading wall.xpm\n");
	data->coin = mlx_xpm_file_to_image(data->mlx,
			"textures/coin.xpm", &data->img_width, &data->img_height);
	if (!data->coin)
		printf("Error loading coin.xpm\n");
}

void	load_exits(t_data *data)
{
	data->exit = mlx_xpm_file_to_image(data->mlx,
			"textures/exit_closed.xpm", &data->img_width, &data->img_height);
	if (!data->exit)
		printf("Error loading exit_closed.xpm\n");
	data->exit_open = mlx_xpm_file_to_image(data->mlx,
			"textures/exit_opened.xpm", &data->img_width, &data->img_height);
	if (!data->exit_open)
		printf("Error loading exit_opened.xpm\n");
}

void	fileloader(t_data *data)
{
	load_player_and_floor(data);
	load_wall_and_coin(data);
	load_exits(data);
	data->img_width = TILE_SIZE;
	data->img_height = TILE_SIZE;
}
