/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   golf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silvertape <silvertape@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 04:26:15 by silvertape        #+#    #+#             */
/*   Updated: 2025/07/02 04:28:44 by silvertape       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ventanillas.h"

void	m(int k, t_data *d)
{
	if (k == 65307)
		exit(0);
	d->text_x += (k == 100) - (k == 97);
	d->text_y += (k == 115) - (k == 119);
	mlx_clear_window(d->mlx, d->window);
	mlx_string_put(d->mlx, d->window, d->text_x, d->text_y, 0xFF00, "Golf!");
}

int	main(void)
{
	t_data	d;

	d.text_x = 400;
	d.text_y = 300;
	d.mlx = mlx_init();
	d.window = mlx_new_window(d.mlx, 800, 600, "Golf");
	mlx_string_put(d.mlx, d.window, d.text_x, d.text_y, 0xFF00, "Golf!");
	mlx_key_hook(d.window, m, &d);
	mlx_loop(d.mlx);
	return (0);
}
