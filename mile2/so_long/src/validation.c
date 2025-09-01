/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silvertape <silvertape@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 02:35:00 by silvertape        #+#    #+#             */
/*   Updated: 2025/07/09 02:46:53 by silvertape       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

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

static int	check_remaining_elements(char **map, int map_height)
{
	int	x;
	int	y;

	x = 0;
	while (x < map_height)
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == 'E' || map[x][y] == 'C'
				|| map[x][y] == 'P' || map[x][y] == '0')
			{
				free_map(map);
				return (0);
			}
			y++;
		}
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

int	check_floodfill(char *filename, int map_height,
		int map_width __attribute__((unused)))
{
	int		fd;
	char	**map;
	int		player_pos[2];

	if (!init_flood_map(filename, map_height, &map, &fd))
		return (0);
	if (!read_and_find_player(fd, map, map_height, player_pos))
		return (0);
	map[map_height] = NULL;
	close(fd);
	floodfill(map, player_pos[0], player_pos[1]);
	if (!check_remaining_elements(map, map_height))
		return (0);
	free_map(map);
	return (1);
}
