/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:25:15 by silvertape        #+#    #+#             */
/*   Updated: 2025/09/01 16:59:59 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	count_total_coins(char **map)
{
	int	y;
	int	x;
	int	count;

	y = 0;
	count = 0;
	if (!map)
		return (0);
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'C')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

/*
** Función principal: inicializa MLX, carga mapa y ejecuta el game loop
** Parámetros: argc - número de argumentos, argv - array de argumentos
** Retorna: 0 si éxito, 1 si error
*/
int	main(int ac, char **av)
{
	t_data	data;

	data.coins_collected = 0;
	data.total_coins = 0;
	if (ac != 2)
	{
		write(2, "Error: Uso: ./so_long <archivo.ber>\n", 36);
		return (1);
	}
	if (!load_map(&data, av[1]))
	{
		write(2, "Error: No se pudo cargar el mapa\n", 33);
		return (1);
	}
	data.total_coins = count_total_coins(data.map);
	if (!init_mlx(&data))
		return (1);
	setup_game(&data);
	free_map(data.map);
	return (0);
}
