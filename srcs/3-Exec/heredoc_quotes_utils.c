/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_quotes_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:47:19 by ajeanne           #+#    #+#             */
/*   Updated: 2023/03/31 14:49:34 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*case_of_dq2(int	*i, int	*j, char *content)
{
	(*i)++;
	while (content[*i + *j] && content[*i + *j] != '"')
		(*j)++;
	content = word_replacing(*i - 1, *i + *j, content,
			ft_substr(content, *i, *j));
	if (!content)
		return (NULL);
	*i = (*i - 1) + *j;
	return (*j = 0, content);
}

int	quote_parsing2(char *content, t_val *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!content)
		return (0);
	while (i <= ft_strlen(content) && content[i])
	{
		if (content[i] == '\'')
			content = case_of_sq(&i, &j, content);
		else if (content[i] == '"')
			content = case_of_dq2(&i, &j, content);
		else
			i++;
	}
	if (!content)
		return (1);
	data->val = content;
	return (0);
}

int	is_error_qm2(char *content, t_val *tmp)
{
	int		i;

	i = -1;
	while (content[++i])
	{
		if (content[i] == '\'')
			if (simple_increment(content, &i))
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
	}
	if (quote_parsing2(tmp->val, tmp))
		return (1);
	return (0);
}
