/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:21:16 by sleon             #+#    #+#             */
/*   Updated: 2023/02/22 19:25:08 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	if (!key_d)
		return (1);
	env = get_env();
	unset_rem(env, key_d);
	return (1);
}
