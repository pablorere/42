/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_flood.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 17:12:00 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/09/14 17:05:17 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	check_remaining_elements(char **map, int map_height)
{
	int	r;
	int	c;

	r = 0;
	while (r < map_height)
	{
		c = 0;
		while (map[r][c])
		{
			if (map[r][c] == 'C' || map[r][c] == 'E')
				return (0);
			c++;
		}
		r++;
	}
	return (1);
}

static int	process_line(char **map, char *line, int x, int *pos)
{
	int	y;

	map[x] = ft_strdup(line);
	if (!map[x])
		return (0);
	y = 0;
	while (map[x][y])
	{
		if (map[x][y] == 'P')
		{
			pos[0] = x;
			pos[1] = y;
		}
		y++;
	}
	return (1);
}

static int	read_and_find_player(int fd, char **map, int map_height, int *pos)
{
	char	*line;
	int		x;

	x = 0;
	while (x < map_height)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!process_line(map, line, x, pos))
		{
			free(line);
			while (--x >= 0)
				free(map[x]);
			free(map);
			close(fd);
			return (0);
		}
		free(line);
		x++;
	}
	return (1);
}

static int	init_flood_map(char *filename, int map_height, char ***map, int *fd)
{
	*fd = open(filename, O_RDONLY);
	if (*fd < 0)
		return (0);
	*map = malloc(sizeof(char *) * (map_height + 1));
	if (!*map)
	{
		close(*fd);
		return (0);
	}
	return (1);
}

int	check_floodfill(char *filename, int map_height, int map_width)
{
	int		fd;
	char	**map;
	int		player_pos[2];

	(void)map_width;
	if (!init_flood_map(filename, map_height, &map, &fd))
		return (print_error("No se pudo preparar el mapa para floodfill"), 0);
	if (!read_and_find_player(fd, map, map_height, player_pos))
		return (0);
	map[map_height] = NULL;
	close(fd);
	floodfill(map, player_pos[0], player_pos[1]);
	if (!check_remaining_elements(map, map_height))
	{
		free_map(map);
		return (print_error("Hay elementos inaccesibles (C o E)"), 0);
	}
	free_map(map);
	return (1);
}
