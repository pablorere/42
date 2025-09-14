/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 02:35:00 by silvertape        #+#    #+#             */
/*   Updated: 2025/09/14 17:05:19 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	validate_rectangular(t_data *data);
int	validate_chars_counts(t_data *data, int *pc, int *ec, int *cc);
int	validate_closed_walls(t_data *data);

int	validate_map_config(t_data *data)
{
	int	pc;
	int	ec;
	int	cc;

	if (!validate_rectangular(data))
		return (0);
	if (!validate_chars_counts(data, &pc, &ec, &cc))
		return (0);
	if (!validate_closed_walls(data))
		return (0);
	return (1);
}
