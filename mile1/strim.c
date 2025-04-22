/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strim.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:01:14 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/04/22 18:58:41 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*trimmed;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (start > end && ft_strchr(set, s1[end]))
		end--;
	trimmed = malloc(sizeof(char) * (end - start + 1));
	ft_strlcpy(trimmed, &s1[start], end-start + 1);
	return (trimmed);
}

int main(void)
{
	const char	*str1 = "                      hola woeld , 9 4,r , ,23,                 ";
	const char	*set = " ";

	printf("%s",ft_strtrim(str1, set));
	return 0;
}
