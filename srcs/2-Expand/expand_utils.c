/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 21:37:20 by ajeanne           #+#    #+#             */
/*   Updated: 2023/02/23 17:05:21 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Add token in list
 *
 * @param content
 * @param next
 * @return t_val*
 */
t_val	*ft_lstnew_token(void *content, t_val *next)
{
	t_val	*new_element;

	new_element = malloc(sizeof(t_val));
	if (!new_element)
		return (NULL);
	new_element->val = content;
	new_element->token = WORD;
	new_element->next = next;
	return (new_element);
}

int	existing_var(char *val)
{
	t_env	*env;
	char	*name;

	name = ft_substr(val, 1, ft_strlen(val));
	env = *get_env();
	while (env && ft_strcmp(env->key, name))
		env = env->next;
	if (!env)
		return (1);
	if (!(env->val))
		return (1);
	return (0);
}

int	ambigous_redirect_checker(t_val *data)
{
	t_val	*tmp;

	tmp = data;
	while (tmp)
	{
		if ((!ft_strcmp(tmp->val, "<") || !ft_strcmp(tmp->val, ">>")
			|| !ft_strcmp(tmp->val, ">")) && tmp->next->val[0] == '$'
			&& existing_var(tmp->next->val))
		{
			msg(tmp->next->val);
			msg(": ambiguous redirect\n");
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
