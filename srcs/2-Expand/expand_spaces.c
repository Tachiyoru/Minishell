/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 21:14:36 by ajeanne           #+#    #+#             */
/*   Updated: 2023/02/28 10:19:31 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Spaces and tab checker increment
 *
 * @param i
 * @param j
 * @param content
 */
void	for_space_checker(int *i, int *j, char *content)
{
	while (content[*i] == -32 || content[*i] == -9)
		(*i)++;
	while (content[*i + *j])
		(*j)++;
}

/**
 * @brief Space and tabs checker
 *
 * @param content
 * @param data
 * @return int
 */
int	space_in_expand(char *content, t_val *data)
{
	int		i;
	int		j;
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
	for_space_checker(&i, &j, content);
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

/**
 * @brief Expand for tabs and spaces main
 *
 * @param content
 * @param data
 * @return int
 */
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
				if (space_in_expand(content, data))
					return (free(content), 1);
				return (0);
			}
			i++;
		}
		i++;
	}
	return (0);
}
