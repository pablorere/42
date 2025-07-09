/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silvertape <silvertape@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:25:15 by silvertape        #+#    #+#             */
/*   Updated: 2025/07/07 16:34:19 by silvertape       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

/*
** Función principal: inicializa MLX, carga mapa y ejecuta el game loop
** Parámetros: argc - número de argumentos, argv - array de argumentos
** Retorna: 0 si éxito, 1 si error
*/
int	main(int ac, char **av)
{
	t_data	data;

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
	if (!init_mlx(&data))
		return (1);
	setup_game(&data);
	free_map(data.map);
	return (0);
}
