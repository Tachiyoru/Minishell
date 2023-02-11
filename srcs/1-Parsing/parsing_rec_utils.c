/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rec_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 12:01:56 by sleon             #+#    #+#             */
/*   Updated: 2023/02/11 17:35:20 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief go to the last node
 *
 * @param data
 * @return the last node to modifie his ->next directly
 */
t_val	*ft_last(t_val **data)
{
	t_val	*tmp;

	tmp = *data;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

/**
 * @brief Set the string in a new node
 *
 * @param str string from char** tab
 * @param data
 * @return int
 */
int	set_val_tab(char *str, t_val **data)
{
	t_val	*new;

	new = malloc(sizeof(t_val));
	if (!new)
		return (1);
	new->next = NULL;
	new->val = ft_strdup(str);
	if (!(*data))
		*data = new;
	else
		ft_last(data)->next = new;
	return (0);
}

/**
 * @brief skip spaces before words if needed
 *
 * @param line
 * @return the starting point after skipping whitespaces
 */
int	word_start(char *line)
{
	int	val;

	val = 0;
	while (line[val] == ' ' || line[val] == '	')
		val++;
	return (val);
}

/**
 * @brief change quote in former functiun to
 * let it know if we are in "" or in '' or not
 * 0 = no quote, 1 = single quote, 2 = double quote.
 *
 * @param c
 * @param quote
 */
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

/**
 * @brief go through str, if we start with an operator check if double
 * else return the size of the word until the next operator.
 *
 * @param line
 * @param start starting point after skiping whitespaces
 * @return the size of the word
 */
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
