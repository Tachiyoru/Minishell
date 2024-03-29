/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:21:24 by sleon             #+#    #+#             */
/*   Updated: 2023/03/20 15:19:50 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_cmd(int fd)
{
	t_env	*env;

	env = *get_env();
	while (env)
	{
		if (env->val)
		{
			ft_putstr_fd(fd, env->key);
			write(fd, "=", 1);
			ft_putstr_fd(fd, env->val);
			write(fd, "\n", 1);
		}
		env = env->next;
	}
	return (g_error = 0, 1);
}
