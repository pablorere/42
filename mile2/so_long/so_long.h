/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:16:20 by silvertape        #+#    #+#             */
/*   Updated: 2025/09/01 17:55:07 by ppaula-s         ###   ########.fr       */
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
#define TILE_SIZE 128

typedef struct s_data
{
	void	*mlx;
	void	*window;
	int		position_x;
	int		position_y;
	int		i;
	int		map_height;
	int		map_width;
	int		coins_collected;
	int		total_coins;
	int		move_count;

	void	*character;
	void	*floor;
	void	*wall;
	void	*coin;
	void	*exit;
	void	*exit_open;
	char	**map;
}	t_data;

/*
** Estructura para almacenar las posiciones de los tiles
*/
typedef struct s_tilepos
{
	int	x;
	int	y;
	int	sx;
	int	sy;
}	t_tilepos;

// Funciones
void	limitwall(t_data *s_data, int xmove, int ymove);
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
int		count_total_coins(char **map);
void	floodfill(char **map, int x, int y);
int		check_floodfill(char *filename, int map_height, int map_width);

/* movement helpers */
int		out_of_bounds(t_data *data, int mx, int my);
void	win_and_exit(t_data *data, int new_x, int new_y);
int		is_exit_blocked(t_data *data, char tile);
void	collect_coin(t_data *data, int mx, int my);
void	perform_move(t_data *data, int nx, int ny);
