/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:13:03 by sleon             #+#    #+#             */
/*   Updated: 2023/02/28 14:09:42 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*is_exec(char *cmd)
{
	int	res;

	if (!ft_strcmp(cmd, "."))
		return (msg("Minishell~ .: filename argument required\n"), NULL);
	else if (!ft_strcmp(cmd, ".."))
		return (msg("..: command not found\n"), NULL);
	else if (!ft_strcmp(cmd, "./"))
		return (msg("Minishell~ ./: Is a directory\n"), NULL);
	res = access(cmd, 1);
	if (res >= 0)
		return (ft_strdup(cmd));
	g_error = 126;
	return (perror(cmd), NULL);
}

/**
 * @brief strdup but modified to make env variable style
 *
 * @param env
 * @return char*
 */
char	*ft_strdup_env(t_env *env)
{
	char	*str;
	int		i;
	int		j;
	int		size;

	size = ft_strlen(env->key) + ft_strlen(env->val);
	str = ft_calloc(size + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while ((i + j) < size)
	{
		if (env->key[i])
			reduce_dup_env_key(env, str, &i);
		else if (!env->key[i] && j == 0)
			str[i + (j++)] = '=';
		else
			reduce_dup_env_val(env, str, &i, &j);
	}
	return (str);
}

/**
 * @brief make envp** needed for the execve functiun
 *
 * @return char**
 */
char	**make_env_tab(void)
{
	char	**start;
	char	**tab;
	t_env	*env;
	int		size;

	env = *get_env();
	size = lst_size(env);
	tab = ft_calloc(sizeof(char *), (size + 1));
	if (!tab)
		return (NULL);
	tab[size] = NULL;
	start = tab;
	while (env)
	{
		*tab = ft_strdup_env(env);
		tab++;
		env = env->next;
	}
	return (start);
}

/**
 * @brief make char** of the cmd needed for the execve functiun
 *
 * @param cmd
 * @return char**
 */
char	**make_cmd_tab(t_val *cmd)
{
	char	**tab;
	char	**tmp;

	tab = malloc(sizeof(char *) * (lst_size_val(cmd) + 1));
	if (!tab)
		return (NULL);
	tab[lst_size_val(cmd)] = NULL;
	tmp = tab;
	while (cmd)
	{
		*tmp = ft_strdup(cmd->val);
		cmd = cmd->next;
		tmp++;
	}
	return (tab);
}

/**
 * @brief look if the functiun called has a path that can be used for execve
 *
 * @param val
 * @param env
 * @return the path if founded else null
 */
char	*pathfinder(char *val, char **env)
{
	char	**path;
	char	*tmp;
	char	*cmd;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH", 4) != NULL)
			tmp = ft_strdup(&env[i][5]);
		i++;
	}
	path = ft_split2(tmp, ':');
	while (*path)
	{
		tmp = ft_strjoin (*path, "/");
		cmd = ft_strjoin (tmp, val);
		free(tmp);
		if (access(cmd, 0) == 0)
			return (cmd);
		free(cmd);
		path++;
	}
	return (NULL);
}
