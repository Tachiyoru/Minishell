/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote_parsing_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:33:47 by ajeanne           #+#    #+#             */
/*   Updated: 2023/02/15 19:00:34 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	case_of_sq(int	*i, int	*j, char *content)
{
	(*i)++;
	while (content[*i + *j] != '\'')
		(*j)++;
	content = word_replacing(*i - 1, *i + *j, content,
			ft_substr(content, *i, *j));
	if (!content)
		return (1);
	*i = (*i - 1) + *j;
	*j = 0;
	return (0);
}

// int	quote_parsing(char *content, t_val *data, t_env *env)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (content[i])
// 	{
// 		if (content[i] == '\'')
// 		{
// 			if (case_of_sq(&i, &j, content))
// 				return (1);
// 		}
// 		else if (content[i] == '"')
// 		{
// 			i++;
// 			while (content[i + j] != '"')
// 			{
// 				if (content[i + j] == '$')
// 				{
// 					if (is_var(content, i + j, data, env))
// 						return (1);
// 					// free(content);
// 					content = data->val;
// 				}
// 				j++;
// 			}
// 			content = word_replacing(i - 1, i + j, content,
// 					ft_substr(content, i, j));
// 			if (!content)
// 				return (1);
// 			i = (i - 1) + j;
// 			j = 0;
// 		}
// 		else
// 		{
// 			if (content[i + j] == '$')
// 			{
// 				if (is_var(content, i + j, data, env))
// 					return (1);
// 				// free(content);
// 				content = data->val;
// 			}
// 			i++;
// 		}
// 	}
// 	data->val = content;
// 	return (0);
// }
