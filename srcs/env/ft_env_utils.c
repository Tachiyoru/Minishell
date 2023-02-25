/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:40:43 by sleon             #+#    #+#             */
/*   Updated: 2023/02/25 00:55:01 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief look for the str find in the env->key
 *
 * @param find the env->key to find
 * @return ptr to env->val of the key if found
 */
char	*find_env(char *find)
{
	t_env	*env;

	if (!find)
		return (NULL);
	env = *get_env();
	while (env)
	{
		if (!ft_strcmp(find, env->key))
			return (env->val);
		env = env->next;
	}
	return (NULL);
}

/**
 * @brief get the last node in the env linkchain
 *
 * @param data the env linkchain
 * @return the last node
 */
t_env	*ft_last_env(t_env **data)
{
	t_env	*tmp;

	tmp = *data;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

/**
 * @brief store the current string of the environnement in the env linkchain
 *
 * @param env	one string from env to add in our linkchain
 * @param env_s
 * @return the new node to add a the end of the final linkchain env
 */
t_env	*init_env2(char *env, t_env *env_s)
{
	int	size;

	size = 0;
	while (env[size] != '=')
		size++;
	env_s->key = ft_strndup(env, size);
	env += size;
	size = 0;
	env_s->val = ft_strdup(++env);
	env_s->next = NULL;
	return (env_s);
}

void	print_list2(t_env *data)
{
	while (data)
	{
		printf("%s - key = %s\n", data->val, data->key);
		data = data->next;
	}
}

/**
 * @brief will make the whole structure that we use to store the env and
 * that will serv in the funciun needing it
 *
 * @param env original env
 * @return pointer to our env
 */
t_env	*init_env(char **env)
{
	t_env	*env_struct;
	t_env	*tmp;
	int		i;

	env_struct = ft_calloc(sizeof(t_env), 1);
	tmp = env_struct;
	i = -1;
	while (*env)
	{
		tmp = ft_calloc(sizeof(t_env), 1);
		tmp = init_env2(*env, tmp);
		env++;
		if (!env_struct->key)
			env_struct = tmp;
		else
			ft_last_env(&env_struct)->next = tmp;
	}
	return (env_struct);
}

// t_env	*add_env(t_env *our_env, char *add)
// {
// }

// t_env	*env_deleter(t_env *our_env, char *delete)
// {
// }
