/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:25:00 by silvertape        #+#    #+#             */
/*   Updated: 2025/09/14 17:13:01 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

/*
** Copia las líneas temporales al mapa final
** Parámetros: data - estructura de datos, temp - líneas temporales
** Retorna: 1 si éxito, 0 si error
*/
static int	copy_lines_to_map(t_data *data, char **temp)
{
	int	i;

	data->map = malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->map)
	{
		free_map(temp);
		return (0);
	}
	i = -1;
	while (++i < data->map_height)
		data->map[i] = temp[i];
	data->map[i] = NULL;
	if (data->map_height > 0)
		data->map_width = ft_strlen(data->map[0]);
	else
		data->map_width = 0;
	free(temp);
	return (1);
}

/*
** Lee las líneas del archivo .ber y las almacena en data->map
** Parámetros: fd - descriptor del archivo abierto, data - estructura de datos
** Retorna: 1 si éxito, 0 si error
*/
static int	read_map_lines(int fd, t_data *data)
{
	char	*line;
	char	**temp;
	int		len;

	data->map_height = 0;
	temp = malloc(sizeof(char *) * 1000);
	if (!temp)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		len = ft_strlen(line);
		if (line[len - 1] == '\n')
			line[len - 1] = '\0';
		temp[data->map_height++] = line;
		line = get_next_line(fd);
	}
	temp[data->map_height] = NULL;
	return (copy_lines_to_map(data, temp));
}

/*
** Abre y lee el archivo del mapa
** Parámetros: filename - nombre del archivo, data - estructura de datos
** Retorna: 1 si éxito, 0 si error
*/
static int	open_and_read_map(char *filename, t_data *data)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error: No se pudo abrir el archivo\n", 35);
		return (0);
	}
	if (!read_map_lines(fd, data))
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

/*
** Carga un mapa desde un archivo .ber en el directorio maps/
** Parámetros: data - estructura de datos, filename - nombre del archivo
** Retorna: 1 si éxito, 0 si error
*/
int	load_map(t_data *data, char *filename)
{
	if (!validate_ber_extension(filename))
	{
		write(2, "Error: El archivo debe tener extensión .ber\n", 45);
		return (0);
	}
	if (!open_and_read_map(filename, data))
		return (0);
	if (!validate_map_config(data))
	{
		if (data->map)
			free_map(data->map);
		data->map = NULL;
		return (0);
	}
	if (!check_floodfill(filename, data->map_height, data->map_width))
	{
		if (data->map)
			free_map(data->map);
		data->map = NULL;
		write(2, "Error: El mapa no es válido (elementos inaccesibles)\n", 53);
		return (0);
	}
	return (1);
}
