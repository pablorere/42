/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silvertape <silvertape@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:16:20 by silvertape        #+#    #+#             */
/*   Updated: 2025/07/09 02:29:15 by silvertape       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/mlx/mlx.h"
#include "lib/libftfull/libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

// Códigos de teclas
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_ESC 65307
#define KEY_CLICK 17

// Configuración del mapa
#define TILE_SIZE 64

typedef struct s_data
{
	void	*mlx;
	void	*window;
	int		position_x;
	int		position_y;
	int		i;
	int		map_height;
	int		map_width;

	void	*character;
	void	*floor;
	void	*wall;
	char	**map;
}	t_data;

// Funciones
void	limitwall(int *x, int *y, int xmove, int ymove);
int		key_hook(int keycode, t_data *data);
void	draw(t_data *data);
void	draw_map(t_data *data);
void	map_to_screen(int map_x, int map_y, int *screen_x, int *screen_y);
int		load_map(t_data *data, char *filename);
int		validate_ber_extension(char *filename);
void	free_map(char **map);
void	fileloader(t_data *data);
int		close_hook(void *param);
int		init_mlx(t_data *data);
void	setup_game(t_data *data);
int		find_player_position(t_data *data);
void	floodfill(char **map, int x, int y);
int		check_floodfill(char *filename, int map_height, int map_width __attribute__((unused)));
