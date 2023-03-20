/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:21:16 by sleon             #+#    #+#             */
/*   Updated: 2023/03/20 15:15:24 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	key_checker_unset(char *key)
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
	return (0);
}

void	error_unset(char *key_val)
{
	g_error = 1;
	msg("unset: `");
	msg(key_val);
	msg("' : not a valid identifier\n");
}

void	free_u_env(t_env *data)
{
	free(data->key);
	free(data->val);
	free(data);
}

void	unset_rem(t_env **data, char *key_d)
{
	t_env	*tmp;
	t_env	*tmp2;

	if (!ft_strcmp((*data)->key, key_d))
	{
		tmp = (*data)->next;
		free_u_env(*data);
		*data = tmp;
		return ;
	}
	tmp = *data;
	tmp2 = tmp;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key_d))
		{
			tmp2->next = tmp->next;
			free_u_env(tmp);
			return ;
		}
		tmp2 = tmp;
		tmp = tmp->next;
	}
}

int	unset_cmd(char *key_d)
{
	t_env	**env;

	if (!key_checker_unset(key_d) || !key_d)
	{
		error_unset(key_d);
		return (1);
	}
	env = get_env();
	unset_rem(env, key_d);
	return (1);
}