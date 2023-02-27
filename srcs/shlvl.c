/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:21:22 by sleon             #+#    #+#             */
/*   Updated: 2023/02/27 19:08:26 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_shlvl(void)
{
	t_env	*env;
	int		lvl;

	env = *get_env();
	while (env)
	{
		if (!ft_strcmp(env->key, "SHLVL"))
			break ;
		env = env->next;
	}
	if (env)
	{
		lvl = ft_atoi(env->val);
		free(env->val);
		lvl++;
		env->val = ft_itoa(lvl);
	}
}
