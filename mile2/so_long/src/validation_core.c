/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_core.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 17:10:00 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/09/14 17:13:01 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	print_error(const char *msg)
{
	write(2, "Error\n", 6);
	if (msg)
	{
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
}

static int	is_allowed(char c)
{
	if (c == '0' || c == '1')
		return (1);
	if (c == 'C' || c == 'E' || c == 'P')
		return (1);
	return (0);
}

int	validate_rectangular(t_data *data)
{
	int	row;
	int	len;

	if (!data->map || data->map_height <= 0 || data->map_width <= 0)
		return (print_error("Mapa vacío o inválido"), 0);
	row = 0;
	while (row < data->map_height)
	{
		len = (int)ft_strlen(data->map[row]);
		if (len != data->map_width)
			return (print_error("El mapa debe ser rectangular"), 0);
		row++;
	}
	return (1);
}

static int	process_cell(char ch, int *pc, int *ec, int *cc)
{
	if (!is_allowed(ch))
		return (print_error("Caracter no permitido"), 0);
	if (ch == 'P')
		(*pc)++;
	else if (ch == 'E')
		(*ec)++;
	else if (ch == 'C')
		(*cc)++;
	return (1);
}

int	validate_chars_counts(t_data *data, int *pc, int *ec, int *cc)
{
	int	r;
	int	c;

	*pc = 0;
	*ec = 0;
	*cc = 0;
	r = -1;
	while (++r < data->map_height)
	{
		c = -1;
		while (++c < data->map_width)
		{
			if (!process_cell(data->map[r][c], pc, ec, cc))
				return (0);
		}
	}
	if (*pc != 1)
		return (print_error("Debe haber exactamente 1 P"), 0);
	if (*ec != 1)
		return (print_error("Debe haber exactamente 1 E"), 0);
	if (*cc < 1)
		return (print_error("Debe haber al menos 1 C"), 0);
	return (1);
}
