/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:21:24 by sleon             #+#    #+#             */
/*   Updated: 2023/02/25 06:33:20 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *data)
{
	while (data && data->key && data->val)
	{
		printf("%s=%s\n", data->key, data->val);
		data = data->next;
	}
}

int	env_cmd(void)
{
	t_env	*env;

	env = *get_env();
	print_env(env);
	return (1);
}
