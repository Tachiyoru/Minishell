/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rec_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 12:01:56 by sleon             #+#    #+#             */
/*   Updated: 2023/02/11 13:36:27 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	word_start(char *line)
{
	int	val;

	val = 0;
	while (line[val] == ' ' || line[val] == '	')
		val++;
	return (val);
}

void	is_quote(char c, int *quote)
{
	if (c == '"')
	{
		if (*quote == 0)
			*quote = 2;
		else if (*quote == 2)
			*quote = 0;
	}
	else if (c == '\'')
	{
		if (*quote == 0)
			*quote = 1;
		else if (*quote == 1)
			*quote = 0;
	}
}

int	word_end(char *line, int start)
{
	int	quote;

	quote = 0;
	if (!line[start])
		return (0);
	if (ft_strchr("><|&", line[start]))
	{
		if (ft_strchr("><|&", line[start + 1]))
			return (2);
		return (1);
	}
	while (line[start])
	{
		is_quote(line[start], &quote);
		if ((line[start] == ' ' || ft_strchr("><|&", line[start])) && !quote)
			break ;
		start++;
	}
	return (start);
}
