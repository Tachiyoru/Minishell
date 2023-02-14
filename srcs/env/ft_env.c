/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:07:51 by sleon             #+#    #+#             */
/*   Updated: 2023/02/14 16:30:20 by sleon            ###   ########.fr       */
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
t_env	**handle_env(char **env, char *add, char *delete)
{
	static t_env	*our_env = NULL;

	(void)add;
	(void)delete;
	if (env)
		our_env = init_env(env);
	return (&our_env);
}
	// else if (add)
		// add_env(our_env, add);
	// else if (delete)
		// our_env = env_deleter(our_env, delete);

/**
 * @brief call the function that has the singleton env stored
 *
 * @return the **t_env tout the functiun that will need it
 */
t_env	**get_env(void)
{
	return (handle_env(NULL, NULL, NULL));
}

/**
 * @brief used for delete a part of the env
 *
 * @param delete the string that we target
 * @return nothing
 */
void	del_from_env(char *delete)
{
	handle_env(NULL, NULL, delete);
}

/**
 * @brief used to add a string in our env
 *
 * @param add the string we want to add
 * @return nothing
 */
void	add_to_env(char *add)
{
	handle_env(NULL, add, NULL);
}

/**
 * @brief give the env tout the functiun that will handle the env
 *
 * @param env the original env
 */
void	store_env(char **env)
{
	handle_env(env, NULL, NULL);
}
