/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silvertape <silvertape@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:31:43 by silvertape        #+#    #+#             */
/*   Updated: 2025/05/10 16:07:31 by silvertape       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*h;

	fd = open("texto.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	h = get_next_line(fd);
	while (h != NULL)
	{
		printf("%s", h);
		free(h);
		h = get_next_line(fd);
	}
	close(fd);
	return (0);
}
