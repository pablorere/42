/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silvertape <silvertape@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 04:01:54 by silvertape        #+#    #+#             */
/*   Updated: 2025/05/29 04:01:55 by silvertape       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char **argv, char **envp)
{
	int	i;

	(void)argc;
	(void)argv;
	i = 0;
	while (envp[i])
	{
		write(1, envp[i], 0);
		while (envp[i][0])
		{
			write(1, envp[i], 1);
			envp[i]++;
		}
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
