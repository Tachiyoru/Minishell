/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:21:18 by sleon             #+#    #+#             */
/*   Updated: 2023/03/21 13:02:33 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_export(char *key_val)
{
	g_error = 1;
	msg("export `");
	msg(key_val);
	msg("' : not a valid identifier\n");
}

int	without_equal(char *key_val)
{
	if (key_checker(key_val))
	{
		if (!existing_key(key_val))
			if (env_add_back(key_val, NULL))
				return (1);
		return (0);
	}
	error_export(key_val);
	return (0);
}

int	with_equal(char *key_val)
{
	char	*val_tmp;
	int		val_start;

	val_start = 0;
	val_start = key_checker(key_val);
	if (!val_start)
	{
		error_export(key_val);
		return (1);
	}
	val_tmp = key_val + val_start + 1;
	key_val[val_start] = '\0';
	if (existing_key_replace_val(key_val, val_tmp))
		return (0);
	if (env_add_back(key_val, val_tmp))
		return (1);
	return (0);
}

void	print_export(int fd)
{
	t_env	*env;

	env = *get_env();
	while (env && env->key)
	{
		if (env && env->key && env->val)
		{
			ft_putstr_fd(fd, "export ");
			ft_putstr_fd(fd, env->key);
			ft_putstr_fd(fd, "=\"");
			ft_putstr_fd(fd, env->val);
			ft_putstr_fd(fd, "\"\n");
		}
		else if (env && env->key)
		{
			ft_putstr_fd(fd, "export ");
			ft_putstr_fd(fd, env->key);
			ft_putstr_fd(fd, "\n");
		}
		env = env->next;
	}
}

int	export_cmd(char *key_val, int fd)
{
	if (!key_val)
		print_export(fd);
	else if (!contain_equals(key_val))
	{
		if (without_equal(key_val))
			return (-1);
		return (1);
	}
	else if (with_equal(key_val))
		return (-1);
	return (1);
}
