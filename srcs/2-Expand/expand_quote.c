/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:53:23 by ajeanne           #+#    #+#             */
/*   Updated: 2023/02/14 16:27:36 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	simple_increment(char *content, int *i)
{
	(*i)++;
	while (content[*i] != '\'')
	{
		if (!content[*i])
			return (1);
		(*i)++;
	}
	return (0);
}

int	is_var(char *content, int i, t_val *data, t_env *env)
{
	int	j;

	j = 0;
	while (content[i + j] && ((content[i + j] >= 'A' && content[i + j] <= 'Z')
		|| (content[i + j] >= 'a' && content[i + j] <= 'z')
		|| content[i + j] == '_'))
		j++;
	j--;
	data->val = var_replacing(i, j, content, env);
	free(content);
	if (!data->val)
		return (1);
	return (0);
}

int	is_error_qm(char *content, t_val *data, t_env *env)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '\'')
			if(simple_increment(content, &i))
				return (1);
		if (content[i] == '"')
		{
			i++;
			while (content[i] != '"')
			{
				if (!content[i])
					return (1);
				if (content[i] == '$')
					if(is_var(content, i, data, env))
						return (1);
				i++;
			}
		}
		i++;
	}
	return (0);
}

int	quote_treatment(t_val *data, t_env *env)
{
	t_val	*tmp;

	tmp = data;
	if (is_error_qm(tmp->val, tmp, env))
		return (1);
	return (0);
}
