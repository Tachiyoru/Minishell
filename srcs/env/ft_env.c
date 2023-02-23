/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:07:51 by sleon             #+#    #+#             */
/*   Updated: 2023/02/23 13:06:17 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief depending on the way it is call it will either init the env, add
 * or delete parts of it
 *
 * @param env original env sent to fill our env
 * @param add the string we want to add
 * @param delete the string we want to delete
 * @return the adress of the static making it a singleton
 */
t_env	**handle_env(char **env)
{
	static t_env	*our_env = NULL;

	if (env)
		our_env = init_env(env);
	return (&our_env);
}

/**
 * @brief call the function that has the singleton env stored
 *
 * @return the **t_env to the functiun that will need it
 */
t_env	**get_env(void)
{
	return (handle_env(NULL));
}

/**
 * @brief give the env tout the functiun that will handle the env
 *
 * @param env the original env
 */
void	store_env(char **env)
{
	handle_env(env);
}
