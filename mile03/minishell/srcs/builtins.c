/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 00:00:00 by ppaula-s          #+#    #+#             */
/*   Updated: 2026/03/23 00:00:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft/libft.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>

static int	is_n_flag(const char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		return (1);
	return (0);
}

static int	is_key_start(char c)
{
	if (ft_isalpha((unsigned char)c) || c == '_')
		return (1);
	return (0);
}

static int	is_key_char(char c)
{
	if (ft_isalnum((unsigned char)c) || c == '_')
		return (1);
	return (0);
}

static int	is_numeric_argument(const char *s)
{
	int	i;

	if (!s || !*s)
		return (0);
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit((unsigned char)s[i]))
			return (0);
		i++;
	}
	return (1);
}

static t_env	*dict_get_node(t_env *env, const char *key)
{
	size_t	key_len;

	if (!key)
		return (NULL);
	key_len = ft_strlen(key);
	while (env)
	{
		if (env->key && ft_strlen(env->key) == key_len
			&& ft_strncmp(env->key, key, key_len) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

static char	*dict_get_value(t_env *env, const char *key)
{
	t_env	*node;

	node = dict_get_node(env, key);
	if (!node)
		return (NULL);
	return (node->value);
}

static t_env	*env_new_node(const char *key, const char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (!node->key)
	{
		free(node);
		return (NULL);
	}
	node->value = NULL;
	if (value)
	{
		node->value = ft_strdup(value);
		if (!node->value)
		{
			free(node->key);
			free(node);
			return (NULL);
		}
	}
	node->next = NULL;
	return (node);
}

static int	env_add_back(t_env **env, t_env *new_node)
{
	t_env	*last;

	if (!env || !new_node)
		return (1);
	if (!*env)
	{
		*env = new_node;
		return (0);
	}
	last = *env;
	while (last->next)
		last = last->next;
	last->next = new_node;
	return (0);
}

static int	set_existing_node(t_env *node, const char *value, int append)
{
	char	*tmp;
	char	*new_value;

	if (!value)
		return (0);
	if (append && node->value)
	{
		tmp = ft_strjoin(node->value, value);
		if (!tmp)
			return (1);
		free(node->value);
		node->value = tmp;
		return (0);
	}
	new_value = ft_strdup(value);
	if (!new_value)
		return (1);
	free(node->value);
	node->value = new_value;
	return (0);
}

static int	env_set_value(t_env **env, const char *key, const char *value,
		int append)
{
	t_env	*node;
	t_env	*new_node;

	if (!env || !key)
		return (1);
	node = dict_get_node(*env, key);
	if (!node)
	{
		new_node = env_new_node(key, value);
		if (!new_node)
			return (1);
		return (env_add_back(env, new_node));
	}
	return (set_existing_node(node, value, append));
}

static int	remove_env_node(t_env **env, const char *key)
{
	t_env	*prev;
	t_env	*cur;

	if (!env || !*env || !key)
		return (0);
	prev = NULL;
	cur = *env;
	while (cur)
	{
		if (ft_strncmp(cur->key, key, ft_strlen(key) + 1) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				*env = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			return (1);
		}
		prev = cur;
		cur = cur->next;
	}
	return (0);
}

static void	free_env_list(t_env **env)
{
	t_env	*cur;
	t_env	*next;

	if (!env)
		return ;
	cur = *env;
	while (cur)
	{
		next = cur->next;
		free(cur->key);
		free(cur->value);
		free(cur);
		cur = next;
	}
	*env = NULL;
}

static int	is_valid_key(const char *key)
{
	int	i;

	if (!key || !key[0] || !is_key_start(key[0]))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!is_key_char(key[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	export_find_sep(const char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (i);
}

static int	export_key_len(const char *arg, int sep, int *append)
{
	int	key_len;

	*append = 0;
	key_len = sep;
	if (sep > 0 && arg[sep - 1] == '+')
	{
		*append = 1;
		key_len--;
	}
	return (key_len);
}

static int	parse_export_arg(const char *arg, char **out_key, char **out_value,
		int *append)
{
	int	sep;
	int	key_len;

	*out_key = NULL;
	*out_value = NULL;
	sep = export_find_sep(arg);
	key_len = export_key_len(arg, sep, append);
	if (key_len <= 0)
		return (1);
	*out_key = ft_substr(arg, 0, key_len);
	if (!*out_key)
		return (1);
	if (arg[sep] == '=')
	{
		*out_value = ft_strdup(arg + sep + 1);
		if (!*out_value)
		{
			free(*out_key);
			*out_key = NULL;
			return (1);
		}
	}
	return (0);
}

static int	env_size(t_env *env)
{
	int	n;

	n = 0;
	while (env)
	{
		n++;
		env = env->next;
	}
	return (n);
}

static int	key_cmp(const char *a, const char *b)
{
	int	i;

	i = 0;
	while (a[i] && b[i] && a[i] == b[i])
		i++;
	return ((unsigned char)a[i] - (unsigned char)b[i]);
}

static void	sort_env_nodes(t_env **nodes, int n)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	while (i < n - 1)
	{
		j = i + 1;
		while (j < n)
		{
			if (key_cmp(nodes[i]->key, nodes[j]->key) > 0)
			{
				tmp = nodes[i];
				nodes[i] = nodes[j];
				nodes[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_export_node(t_env *node)
{
	if (node->value)
		printf("declare -x %s=\"%s\"\n", node->key, node->value);
	else
		printf("declare -x %s\n", node->key);
}

static void	print_export_list(t_env *env)
{
	t_env	**nodes;
	t_env	*cur;
	int		n;
	int		i;

	n = env_size(env);
	if (n == 0)
		return ;
	nodes = malloc(sizeof(t_env *) * n);
	if (!nodes)
		return ;
	i = 0;
	cur = env;
	while (cur)
	{
		nodes[i++] = cur;
		cur = cur->next;
	}
	sort_env_nodes(nodes, n);
	i = 0;
	while (i < n)
		print_export_node(nodes[i++]);
	free(nodes);
}

int	ft_echo(char **args, t_env **env)
{
	int		i;
	bool	print_newline;

	(void)env;
	i = 1;
	print_newline = true;
	while (args[i] && is_n_flag(args[i]))
	{
		print_newline = false;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (print_newline)
		printf("\n");
	return (0);
}

int	ft_pwd(char **args, t_env **env)
{
	char	cwd[PATH_MAX];

	(void)env;
	if (args[1])
	{
		fprintf(stderr, "minishell: pwd: too many arguments\n");
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (0);
	}
	perror("minishell: pwd");
	return (1);
}

int	ft_env(char **args, t_env **env)
{
	t_env	*current;

	if (args[1])
	{
		fprintf(stderr, "minishell: env: too many arguments\n");
		return (1);
	}
	if (!env || !*env)
		return (1);
	current = *env;
	while (current)
	{
		if (current->value != NULL)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (0);
}

int	env(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
	{
		printf("Error: environment not available\n");
		return (1);
	}
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

static int	exit_numeric_error(char *arg, t_env **env)
{
	fprintf(stderr, "minishell: exit: %s: numeric argument required\n", arg);
	free_env_list(env);
	exit(255);
}

static long	parse_exit_status(char *arg, t_env **env)
{
	long	status;

	if (!is_numeric_argument(arg))
		exit_numeric_error(arg, env);
	errno = 0;
	status = strtol(arg, NULL, 10);
	if (errno == ERANGE)
		exit_numeric_error(arg, env);
	return (status);
}

int	ft_exit(char **args, t_env **env)
{
	long	exit_status;

	exit_status = 0;
	printf("exit\n");
	if (args[1])
	{
		if (args[2])
		{
			fprintf(stderr, "minishell: exit: too many arguments\n");
			return (1);
		}
		exit_status = parse_exit_status(args[1], env);
	}
	free_env_list(env);
	exit((unsigned char)exit_status);
}

static int	set_cd_oldpwd(t_env **env, char *oldpwd)
{
	if (!oldpwd[0])
		return (0);
	if (env_set_value(env, "OLDPWD", oldpwd, 0) != 0)
		return (1);
	return (0);
}

static int	set_cd_pwd(t_env **env)
{
	char	newpwd[PATH_MAX];

	if (!getcwd(newpwd, sizeof(newpwd)))
		return (1);
	if (env_set_value(env, "PWD", newpwd, 0) != 0)
		return (1);
	return (0);
}

int	ft_cd(char **args, t_env **env)
{
	char	*path;
	char	oldpwd[PATH_MAX];

	if (!env)
		return (1);
	if (args[1] && args[2])
		return (fprintf(stderr, "minishell: cd: too many arguments\n"), 1);
	path = args[1];
	if (!path)
	{
		path = dict_get_value(*env, "HOME");
		if (!path)
			return (fprintf(stderr, "minishell: cd: HOME not set\n"), 1);
	}
	if (!getcwd(oldpwd, sizeof(oldpwd)))
		oldpwd[0] = '\0';
	if (chdir(path) != 0)
		return (perror("minishell: cd"), 1);
	set_cd_oldpwd(env, oldpwd);
	set_cd_pwd(env);
	return (0);
}

int	ft_unset(char **args, t_env **env)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (!env || !*env)
		return (0);
	while (args[i])
	{
		if (!is_valid_key(args[i]))
		{
			fprintf(stderr, "minishell: unset: `%s': not a valid identifier\n",
				args[i]);
			status = 1;
		}
		else
			remove_env_node(env, args[i]);
		i++;
	}
	return (status);
}

static int	handle_export_one(char *arg, t_env **env)
{
	char	*key;
	char	*value;
	int		append;
	int		ret;

	key = NULL;
	value = NULL;
	append = 0;
	if (parse_export_arg(arg, &key, &value, &append) != 0 || !is_valid_key(key))
		ret = 1;
	else
		ret = env_set_value(env, key, value, append);
	if (ret == 1)
		fprintf(stderr,
			"minishell: export: `%s': not a valid identifier\n", arg);
	free(key);
	free(value);
	return (ret);
}

int	ft_export(char **args, t_env **env)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (!env)
		return (1);
	if (!args[1])
	{
		print_export_list(*env);
		return (0);
	}
	while (args[i])
	{
		if (handle_export_one(args[i], env) != 0)
			status = 1;
		i++;
	}
	return (status);
}
