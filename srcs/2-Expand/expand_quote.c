/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:53:23 by ajeanne           #+#    #+#             */
/*   Updated: 2023/03/21 15:59:57 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief * -1 for char in negative
 *
 * @param data
 */
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

/**
 * @brief Clear empty content in data
 *
 * @param data
 */
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

/**
 * @brief Increment in case of simple quote
 *
 * @param content
 * @param i
 * @return int
 */
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

/**
 * @brief Check if we have the right number of quotes
 *
 * @param content
 * @return int
 */
int	is_error_qm(char *content, t_val *tmp, t_val *tmp_prev)
{
	int	i;

	i = 0;
	while (content[i])
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
		i++;
	}
	if (quote_parsing(tmp->val, tmp))
		return (1);
	if (!tmp_prev && expand_space(tmp->val, tmp))
		return (1);
	return (0);
}

/**
 * @brief Main treatment of expand, calling all parts
 *
 * @param data
 * @return int
 */
int	quote_treatment(t_val *data)
{
	t_val	*tmp;
	t_val	*tmp_prev;

	tmp = data;
	tmp_prev = NULL;
	if (ambigous_redirect_checker(data))
		return (1);
	while (tmp)
	{
		if (tmp->token == WORD || tmp->token == FD)
		{
			if (is_error_qm(tmp->val, tmp, tmp_prev))
				return (1);
			back_to_positive(tmp);
			if (!ft_strcmp(tmp->val, "echo"))
				tmp_prev = tmp;
		}
		else
			tmp_prev = NULL;
		tmp = tmp->next;
	}
	if (data)
		return (clean_data(&data), exec(data), 0);
	else
		return (printf("Minishell ~ : command not found\n"), 0);
}
