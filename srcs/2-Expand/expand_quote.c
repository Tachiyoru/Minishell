/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:53:23 by ajeanne           #+#    #+#             */
/*   Updated: 2023/02/15 21:21:19 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	is_error_qm(char *content)
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
	return (0);
}

int	quote_treatment(t_val *data)
{
	t_val	*tmp;

	tmp = data;
	while (tmp)
	{
		if (is_error_qm(tmp->val))
			return (1);
		if (quote_parsing(tmp->val, tmp))
			return (1);
		if (expand_space(tmp->val, tmp))
			return (1);
		back_to_positive(tmp);
		tmp = tmp->next;
	}
	clean_data(&data);
	print_list(data);
	// exec(data);
	return (0);
}

// '"klasjgdg'"'""suite'"'fin' '"'"'"$USER"'"
