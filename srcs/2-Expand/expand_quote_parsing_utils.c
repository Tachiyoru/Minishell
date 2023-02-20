/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote_parsing_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:33:47 by ajeanne           #+#    #+#             */
/*   Updated: 2023/02/20 18:19:19 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*case_of_sq(int	*i, int	*j, char *content)
{
	(*i)++;
	while (content[*i + *j] && content[*i + *j] != '\'')
		(*j)++;
	content = word_replacing(*i - 1, *i + *j, content,
			ft_substr(content, *i, *j));
	if (!content)
		return (NULL);
	*i = (*i - 1) + *j;
	*j = 0;
	return (content);
}

char	*case_of_dq(int	*i, int	*j, char *content, t_val *data)
{
	(*i)++;
	while (content[*i + *j] && content[*i + *j] != '"')
	{
		if (content[*i + *j] == '$' && ((content[(*i + *j) + 1] >= 'A'
					&& content[(*i + *j) + 1] <= 'Z')
				|| (content[(*i + *j) + 1] >= '0'
					&& content[(*i + *j) + 1] <= '9')
				|| (content[(*i + *j) + 1] >= 'a'
					&& content[(*i + *j) + 1] <= 'z')
				|| content[(*i + *j) + 1] == '_'
				|| content[(*i + *j) + 1] == '?'))
		{
			if (is_var(content, *i + *j, data, i))
				return (NULL);
			content = data->val;
		}
		(*j)++;
	}
	content = word_replacing(*i - 1, *i + *j, content,
			ft_substr(content, *i, *j));
	if (!content)
		return (NULL);
	*i = (*i - 1) + *j;
	*j = 0;
	return (content);
}

char	*case_of_nq(int	*i, int	*j, char *content, t_val *data)
{
	while (content[*i + *j] == '$' && ((content[(*i + *j) + 1] >= 'A'
				&& content[(*i + *j) + 1] <= 'Z')
			|| (content[(*i + *j) + 1] >= 'a' && content[(*i + *j) + 1] <= 'z')
			|| (content[(*i + *j) + 1] >= '0' && content[(*i + *j) + 1] <= '9')
			|| content[(*i + *j) + 1] == '_' || content[(*i + *j) + 1] == '?'))
	{
		if (is_var(content, *i + *j, data, i))
			return (NULL);
		content = data->val;
	}
	(*i)++;
	return (content);
}

int	quote_parsing(char *content, t_val *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (content[i])
	{
		if (content[i] == '\'')
		{
			content = case_of_sq(&i, &j, content);
		}
		else if (content[i] == '"')
		{
			content = case_of_dq(&i, &j, content, data);
		}
		else
		{
			content = case_of_nq(&i, &j, content, data);
		}
	}
	if (!content)
		return (1);
	data->val = content;
	return (0);
}