#include "../include/functions.h"

/*
** Free all pointers in a split (array of strings)
** Usage: after using ft_split, call free_split to free all memory
*/
void free_split(char **split)
{
	int i;

	if (!split)
		return;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char *search_env(char **env, char *key)
{
	int i;
	size_t key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
			return (env[i] + key_len + 1);
		i++;
	}
	return (NULL);
}

char *find_command_path(char *command, char **envp)
{
	char **paths;
	char *path_env;
	char *full_path;
	char *temp;
	int i;

	if (!command || !envp)
		return (NULL);
	if (access(command, X_OK) == 0)
		return (ft_strdup(command));
	path_env = search_env(envp, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, command);
		free(temp);
		if (access(full_path, X_OK) == 0)
		{
			free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_split(paths);
	return (NULL);
}

void execute_command(char **argv, char **envp)
{
	char *cmd_path;
	pid_t pid;
	int status;

	cmd_path = find_command_path(argv[0], envp);
	if (!cmd_path)
		return;
	pid = fork();
	if (pid == -1)
	{
		free(cmd_path);
		return;
	}
	if (pid == 0)
	{
		execve(cmd_path, argv, envp);
		exit(1);
	}
	else
	{
		waitpid(pid, &status, 0);
		free(cmd_path);
	}
}

static int	count_args(char *str)
{
	int	count;
	int	in_quotes;
	int	i;

	count = 0;
	in_quotes = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' && !in_quotes)
			i++;
		if (str[i])
		{
			count++;
			while (str[i] && (str[i] != ' ' || in_quotes))
			{
				if (str[i] == '"')
					in_quotes = !in_quotes;
				i++;
			}
		}
	}
	return (count);
}

static char	*extract_arg(char *str, int *pos)
{
	int		start;
	int		len;
	int		in_quotes;
	char	*result;

	in_quotes = 0;
	while (str[*pos] == ' ')
		(*pos)++;
	start = *pos;
	len = 0;
	while (str[*pos] && (str[*pos] != ' ' || in_quotes))
	{
		if (str[*pos] == '"')
		{
			in_quotes = !in_quotes;
			(*pos)++;
		}
		else
		{
			len++;
			(*pos)++;
		}
	}
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	len = 0;
	in_quotes = 0;
	while (str[start] && (str[start] != ' ' || in_quotes))
	{
		if (str[start] == '"')
			in_quotes = !in_quotes;
		else
			result[len++] = str[start];
		start++;
	}
	result[len] = '\0';
	return (result);
}

char	**split_with_quotes(char *str)
{
	char	**result;
	int		count;
	int		i;
	int		pos;

	if (!str)
		return (NULL);
	count = count_args(str);
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	i = 0;
	pos = 0;
	while (i < count)
	{
		result[i] = extract_arg(str, &pos);
		if (!result[i])
		{
			free_split(result);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}