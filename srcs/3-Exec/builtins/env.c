/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:21:24 by sleon             #+#    #+#             */
/*   Updated: 2023/02/21 23:22:43 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *data)
{
	while (data && data->key)
	{
		printf("%s=%s\n", data->key, data->val);
		data = data->next;
	}
}

int	env_cmd()
{
	t_env	*env;

	env = *get_env();
	print_env(env);
	return (1);
}
