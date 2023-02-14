/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:53:23 by ajeanne           #+#    #+#             */
/*   Updated: 2023/02/14 23:48:41 by ajeanne          ###   ########.fr       */
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
		|| content[i + j] == '_'
		|| content[i + j] == '$'))
		j++;
	j--;
	data->val = var_replacing(i, i + j, content, env);
	// free(content);
	if (!data->val)
		return (1);
	return (0);
}

int	is_error_qm(char *content)
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
				i++;
			}
		}
		i++;
	}
	return (0);
}

int	quote_parsing(char *content, t_val *data, t_env *env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (content[i])
	{
		if (content[i] == '\'')
		{
			i++;
			while (content[i + j] != '\'')
				j++;
			content = word_replacing(i - 1, i + j, content, ft_substr(content, i, j));
			if (!content)
				return (1);
			i = (i - 1) + j;
			j = 0;
		}
		else if (content[i] == '"')
		{
			i++;
			while (content[i + j] != '"')
			{
				if (content[i + j] == '$')
				{
					if(is_var(content, i + j, data, env))
						return (1);
					// free(content);
					content = data->val;
				}
				j++;
			}
			content = word_replacing(i - 1, i + j, content, ft_substr(content, i, j));
			if (!content)
				return (1);
			i = (i - 1) + j;
			j = 0;
		}
		else
		{
			if (content[i + j] == '$')
			{
				if(is_var(content, i + j, data, env))
					return (1);
				// free(content);
				content = data->val;
			}
			i++;
		}
	}
	data->val = content;
	return (0);
}

int	space_in_expand(char *content, t_val *data)
{
	int	i;
	int	j;
	char	*token1;
	char	*token2;

	i = 0;
	j = 0;
	token1 = NULL;
	token2 = NULL;
	while (content[i] != -32 && content[i] != -9)
		i++;
	token1 = ft_substr(content, 0, i);
	if (!token1)
		return (1);
	while (content[i] == -32 || content[i] == -9)
		i++;
	while (content[i + j])
		j++;
	token2 = ft_substr(content, i, j);
	if (!token2)
		return (1);
	free(data->val);
	data->val = token1;
	data->next = ft_lstnew_token(token2, data->next);
	if (!data->next)
		return (1);
	return (0);
}

int	expand_space(char *content, t_val *data)
{
	int	i;

	i = 0;
	while (content[i])
	{
		while (content[i] < 0)
		{
			if (content[i] == -32 || content[i] == -9)
			{
				if(space_in_expand(content, data))
					return (1);
				return (0);
			}
			i++;
		}
		i++;
	}
	return (0);
}

void	back_to_positive(t_val *data)
{
	int	i;

	i = 0;
	while (data->val[i])
	{
		if (data->val[i] < 0)
			data->val[i] = data->val[i] * -1;
		i++;
	}
}

void	clean_data(t_val **data)
{
	t_val	*tmp;
	t_val	*tmp2;

	tmp = *data;
	tmp2 = *data;
	while (tmp && !(*(tmp->val)))
		tmp = tmp->next;
	*data = tmp;
	tmp = tmp2;
	while (tmp2)
	{
		if (!(*(tmp2->val)))
		{
			tmp->next = tmp2->next;
			free(tmp2->val);
			free(tmp2);
			tmp2 = tmp;
		}
		tmp = tmp2;
		tmp2 = tmp2->next;
	}
}

int	quote_treatment(t_val *data)
{
	t_val	*tmp;
	t_env	**env;

	env = get_env();
	tmp = data;
	while (tmp)
	{
		if (is_error_qm(tmp->val))
			return (1);
		if (quote_parsing(tmp->val, tmp, *env))
			return (1);
		if (expand_space(tmp->val, tmp))
			return (1);
		back_to_positive(tmp);
		tmp = tmp->next;
	}
	clean_data(&data);
	print_list(data);
	return (0);
}

// '"klasjgdg'"'""suite'"'fin' '"'"'"$USER"'"
