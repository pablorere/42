/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:00:28 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/04/27 17:00:28 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	update_buffer(char *buffer)
{
	int	i;
	int	j;

	i = 0;
	j = ft_findnewline(buffer);
	if (j == -1)
		return ;
	i++;
	while (buffer[i + j] != '\0')
		buffer[i] = buffer[i + j++];
	buffer[i] = '\0';
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	char		*tmp;
	int			bytes_read;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = 1;
	line = NULL;
	line = ft_strjoin(NULL, buffer);
	while (ft_findnewline(buffer) == -1 && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(line);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		tmp = ft_strjoin(line, buffer);
		free(line);
		line = tmp;
	}
	if (!line || (line[0] == '\0' && bytes_read == 0))
	{
		free(line);
		return (NULL);
	}
	update_buffer(buffer);
	return (line);
}

int	ft_findnewline(const char *s)
{
	int	a;

	a = 0;
	while (s[a] != '\0')
	{
		if (s[a] == '\n')
			return (a);
		a++;
	}
	return (-1);
}
