/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_walls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 17:15:00 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/09/14 17:05:17 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	validate_closed_walls(t_data *data)
{
	int	c;
	int	r;

	c = -1;
	while (++c < data->map_width)
	{
		if (data->map[0][c] != '1')
			return (print_error("Borde superior abierto"), 0);
		if (data->map[data->map_height - 1][c] != '1')
			return (print_error("Borde inferior abierto"), 0);
	}
	r = -1;
	while (++r < data->map_height)
	{
		if (data->map[r][0] != '1')
			return (print_error("Borde izquierdo abierto"), 0);
		if (data->map[r][data->map_width - 1] != '1')
			return (print_error("Borde derecho abierto"), 0);
	}
	return (1);
}
