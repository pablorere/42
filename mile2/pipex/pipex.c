/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silvertape <silvertape@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:41:59 by silvertape        #+#    #+#             */
/*   Updated: 2025/05/29 03:50:34 by silvertape       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_parent(char **av, char **envp, int *straw)
{
	int	output;

	output = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output == -1)
		error();
	dup2(straw[0], 0);
	dup2(output, 1);
	close(straw[0]);
	close(straw[1]);
	close(output);
	ft_execute(av[3], envp);
}

void	ft_child(char **av, char **envp, int *straw)
{
	int	input;

	input = open(av[1], O_RDONLY);
	if (input == -1)
		error();
	dup2(input, 0);
	dup2(straw[1], 1);
	close(input);
	close(straw[0]);
	close(straw[1]);
	ft_execute(av[2], envp);
}

int	main(int ac, char **av, char **envp)
{
	int		straw[2];
	pid_t	pid1;

	if (ac == 5)
	{
		if (pipe(straw) == -1)
			error();
		pid1 = fork();
		if (pid1 == -1)
			error();
		if (pid1 == 0)
			ft_child(av, envp, straw);
		waitpid(pid1, NULL, 0);
		ft_parent(av, envp, straw);
	}
	else
	{
		ft_putstr_fd("error: bad arguments", 2);
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
	}
}
