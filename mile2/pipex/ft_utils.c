/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silvertape <silvertape@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 00:43:10 by silvertape        #+#    #+#             */
/*   Updated: 2025/05/29 04:21:59 by silvertape       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(void)
{
	perror("Error");
	exit (EXIT_FAILURE);
}

char	*ft_local(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*part_path;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (path && access(path, F_OK) == 0)
			return (free_choice(paths, path, 1));
		free(path);
	}
	free_choice(paths, NULL, 0);
	return (NULL);
}

void	ft_execute(char *av, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(av, ' ');
	if (!cmd)
		error();
	path = ft_local(cmd[0], envp);
	if (!path)
	{
		free_cmd_array(cmd);
		error();
	}
	if (execve(path, cmd, envp) == -1)
	{
		free(path);
		free_cmd_array(cmd);
		error();
	}
}

void	free_cmd_array(char **cmd)
{
	int	i;

	if (!cmd)
		return ;
	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

char	*free_choice(char **paths, char *path, int boolean)
{
	int	i;

	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
	if (boolean == 1)
		return (path);
	return (NULL);
}
