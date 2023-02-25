/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:21:18 by sleon             #+#    #+#             */
/*   Updated: 2023/02/25 03:23:22 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	without_equal(char *key_val)
{
	if (key_checker(key_val))
		if (!existing_key(key_val))
			if (env_add_back(key_val, NULL))
				return (1);
	return (0);
}

int	with_equal(char *key_val)
{
	char	*val_tmp;
	int		val_start;

	val_start = 0;
	val_start = key_checker(key_val);
	if (!val_start)
		return (1);
	val_tmp = key_val + val_start + 1;
	key_val[val_start] = '\0';
	if (existing_key_replace_val(key_val, val_tmp))
		return (0);
	if (env_add_back(key_val, val_tmp))
		return (1);
	return (0);
}

void	print_export(void)
{
	t_env	*env;

	env = *get_env();
	while (env && env->key)
	{
		if (env && env->key && env->val)
			printf("export %s=\"%s\"\n", env->key, env->val);
		else if (env && env->key)
			printf("export %s\n", env->key);
		env = env->next;
	}
}

int	export_cmd(char *key_val)
{
	if (!key_val)
		print_export();
	else if (!contain_equals(key_val))
	{
		if (without_equal(key_val))
			return (-1);
		return (0);
	}
	else if (with_equal(key_val))
		return (-1);
	return (0);
}
