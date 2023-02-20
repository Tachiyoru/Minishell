/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:13:03 by sleon             #+#    #+#             */
/*   Updated: 2023/02/20 17:10:18 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//faire une fction pour les tailles des str pour les lignes
char	*ft_strdup_env(t_env *env)
{
	char	*str;
	int		i;
	int		j;
	int		size;

	size = 0;
	i = -1;
	while (env->key[size])
		size++;
	while (env->val[++i])
		size++;
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

int	lst_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

int	lst_size_val(t_val *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
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

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (little[j] != '\0' && big[i + j] == little[j] && i + j < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)big + i);
			j++;
		}
		i++;
	}
	return (0);
}

int	word_count(char *str, char set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] == set)
			i++;
		while (str[i] && str[i] != set)
		{
			if (str[i + 1] == set || str[i + 1] == '\0')
				j++;
			i++;
		}
	}
	return (j);
}

int	char_count(char *str, char set, int pos)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		while (str[i] && str[i] == set)
			i++;
		while (str[i] && str[i] != set)
		{
			if (j == pos)
				k++;
			if (str[i + 1] == set || str[i + 1] == '\0')
				j++;
			i++;
		}
	}
	return (k);
}

char	*ft_putword(char *str, char *tab, char set, int pos)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		while (str[i] && str[i] == set)
			i++;
		while (str[i] && str[i] != set)
		{
			if (j == pos)
			{
				tab[k] = str[i];
				k++;
			}
			if (str[i + 1] == set || str[i + 1] == '\0')
				j++;
			i++;
		}
	}
	tab[k] = '\0';
	return (tab);
}

char	**ft_split2(char	*str, char set)
{
	int		j;
	char	**tab;

	j = 0;
	if (!str)
		return (NULL);
	tab = ft_calloc(sizeof(char *), word_count(str, set) + 1);
	if (!tab)
		return (NULL);
	while (j < word_count(str, set))
	{
		tab[j] = ft_calloc(1, char_count(str, set, j) + 1);
		if (!tab[j])
			return (free_tab(tab), NULL);
		tab[j] = ft_putword(str, tab[j], set, j);
		j++;
	}
	tab[j] = 0;
	free(str);
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
