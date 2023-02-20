/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:13:03 by sleon             #+#    #+#             */
/*   Updated: 2023/02/20 18:14:50 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup_env(t_env *env)
{
	char	*str;
	int		i;
	int		j;
	int		size;

	size = 0;
	size += ft_strlen(env->key);
	size += ft_strlen(env->val);
	str = (char *)ft_calloc((sizeof(char)), (size + 2));
	if (str == 0)
		return (NULL);
	i = -1;
	j = -1;
	while (++i < size)
	{
		if (env->key[i])
			str[i] = env->key[i];
		else if (!env->key[i] && ++j == 0)
			str[i] = '=';
		else
			str[i] = env->val[j++];
	}
	str[i] = '\0';
	return (str);
}

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
