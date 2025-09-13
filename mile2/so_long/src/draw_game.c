/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:00:00 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/09/13 15:59:07 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	draw(t_data *data)
{
	char	move_str[50];

	mlx_clear_window(data->mlx, data->window);
	draw_map(data);
	sprintf(move_str, "Moves: %d", data->move_count);
	mlx_string_put(data->mlx, data->window, 10, 20, 0xFFFFFF, move_str);
}
