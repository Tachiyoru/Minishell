/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:21:18 by sleon             #+#    #+#             */
/*   Updated: 2023/02/22 23:01:16 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*val_gen(char *key_val, int *no_val)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (key_val[i])
	{
		if (key_val[i] == '=')
		{
			i++;
			if (key_val[i])
			{
				while (key_val[i + j])
					j++;
				return (ft_substr(key_val, i, i + j));
			}
			*no_val = 1;
			return (ft_substr(key_val, 0, 0));
		}
		i++;
	}
	return (NULL);
}

char	*key_gen(char *key_val)
{
	int	i;

	i = 0;
	while (key_val[i])
	{
		if (key_val[i] == '=')
			return (ft_substr(key_val, 0, i));
		i++;
	}
	return (NULL);
}

int	key_checker(char *key)
{
	int	i;

	i = 1;
	if ((key[0] >= '0' && key[0] <= '9')
		|| ((key[0] <= 'A' || (key[0] >= 'Z'
		&& key[0] <= 'a') || key[0] >= 'z')
		&& key[0] != '_'))
		return (1);
	while (key[i] && ((key[i] >= '0' && key[i] <= '9')
		|| (key[i] >= 'A' && key[i] <= 'Z')
		|| (key[i] >= 'a' && key[i] <= 'z')
		|| key[i] == '_'))
		i++;
	if (!key[i])
		return (0);
	return (1);
}

int	env_add_back(t_env *env, char *key, char *val)
{
	t_env	*tmp;
	t_env	*tmp_prev;

	tmp = env;
	while (tmp)
	{
		tmp_prev = tmp;
		tmp = tmp->next;
	}
	tmp_prev->next = lst_env_new(key, val);
	if (!tmp_prev->next)
		return (1);
	return (0);
}

int	export_cmd(char *key_val)
{
	char	*key;
	char	*val;
	int		no_val;
	t_env	*env;

	env = *get_env();
	if (!key_val)
	{
		while (env && env->key)
		{
			printf("%s=\"%s\"\n", env->key, env->val);
			env = env->next;
		}
		return (0);
	}
	no_val = 0;
	key = key_gen(key_val);
	val = val_gen(key_val, &no_val);
	if (!key || (!val && !no_val))
		return (-1);
	if (key_checker(key))
		return (0);
	if (env_add_back(env, key, val))
		return (-1);
	return (1);
}
