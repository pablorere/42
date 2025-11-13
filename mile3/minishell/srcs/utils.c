#include "../include/functions.h"

/*
** Free all pointers in a split (array of strings)
** Usage: after using ft_split, call free_split to free all memory
*/
void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
