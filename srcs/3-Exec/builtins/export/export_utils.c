/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 03:14:26 by ajeanne           #+#    #+#             */
/*   Updated: 2023/03/20 15:14:53 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	existing_key_replace_val(char *key, char *val)
{
	t_env	*env;

	env = *get_env();
	while (env)
	{
		if (!ft_strcmp(key, env->key))
		{
			if (env->val)
				free(env->val);
			env->val = ft_strdup(val);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int	existing_key(char *key)
{
	t_env	*env;

	env = *get_env();
	while (env)
	{
		if (!ft_strcmp(key, env->key))
			return (1);
		env = env->next;
	}
	return (0);
}

int	key_checker(char *key)
{
	int	i;

	i = 1;
	if ((key[0] >= '0' && key[0] <= '9')
		|| ((key[0] < 'A' || (key[0] > 'Z'
					&& key[0] < 'a') || key[0] > 'z')
			&& key[0] != '_'))
		return (0);
	while (key[i] && ((key[i] >= '0' && key[i] <= '9')
			|| (key[i] >= 'A' && key[i] <= 'Z')
			|| (key[i] >= 'a' && key[i] <= 'z')
			|| key[i] == '_'))
		i++;
	if (!key[i])
		return (1);
	else if (key[i] == '=')
		return (i);
	return (0);
}

int	env_add_back(char *key, char *val)
{
	t_env	*tmp;
	t_env	*tmp_prev;
	t_env	*env;

	env = *get_env();
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

int	contain_equals(char *key_val)
{
	int	i;

	i = 0;
	while (key_val && key_val[i])
	{
		if (key_val[i] == '=')
			return (1);
		i++;
	}
	return (0);
}